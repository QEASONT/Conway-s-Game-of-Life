#include "unity.h"
#include "read_write.h"
#include "lifegame.h"

void test_create_map()
{
  unsigned int Maxrow = 50;
  unsigned int Maxcol = 50;
  int **map = create_map(&Maxrow, &Maxcol);
  TEST_ASSERT_NOT_NULL_MESSAGE(map, "create_map returned a null pointer");
  Maxcol = 0;
  Maxrow = 0;
  map = create_map(&Maxrow, &Maxcol);
  TEST_ASSERT_NULL_MESSAGE(map, "create_map returned a not null pointer");
  // TEST_ASSERT_EQUAL_PTR_MESSAGE(&c,o->customer,"order create returned an order with the wrong customer");
  // TEST_ASSERT_NULL_MESSAGE(o->dishes,"order_create returned an order with a Non-NULL array");
  // TEST_ASSERT_EQUAL_INT(0,o->order_length);
}
void test_check_next()
{
  unsigned Maxrow = 5;
  unsigned Maxcol = 5;
  int **map = create_map(&Maxrow, &Maxcol);
  map[2][0] = 1;
  map[1][2] = 1;
  map[2][2] = 1;
  map[3][2] = 1;
  check_next(&Maxrow, &Maxcol, map);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, map[1][1], "check_next calculate next map[1][1] is not 1.");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, map[0][0], "check_next calculate next map[1][1] is not 0.");
}
void test_insert_map()
{
  unsigned int Maxrow;
  unsigned int Maxcol;
  FILE *file = fopen("test.txt", "r");

  read_file(file, &Maxrow, &Maxcol);
  fclose(file);
  int **map = create_map(&Maxrow, &Maxcol);
  file = fopen("test.txt", "r");
  insert_map(file, &Maxrow, &Maxcol, map);
  fclose(file);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, map[1][2], "insert_map map[1][2] is not 1.");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, map[2][1], "insert_map map[2][1] is not 0.");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, map[3][2], "insert_map map[3][2] is not 1.");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, map[3][3], "insert_map map[3][3] is not 0.");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, map[4][0], "insert_map map[4][0] is not 0.");
  file = NULL;
  int infback = insert_map(file, &Maxrow, &Maxcol, map);
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, infback, "insert_map while file = NULL, return not -1.");
  file = fopen("test.txt", "r");
  Maxcol = 0;
  Maxrow = 2;
  infback = insert_map(file, &Maxrow, &Maxcol, map);
  fclose(file);
  TEST_ASSERT_EQUAL_INT_MESSAGE(-2, infback, "insert_map while file != NULL,Maxrow=0 return not -2.");
  printf("%d**************",infback);
  file = fopen("test.txt", "r");
  Maxcol = 2;
  Maxrow = 0;
  infback = insert_map(file, &Maxrow, &Maxcol, map);
  fclose(file);
  TEST_ASSERT_EQUAL_INT_MESSAGE(-2, infback, "insert_map while file != NULL,Maxcol=0 return not -2.");
}
void test_read_file()
{
  unsigned int Maxrow;
  unsigned int Maxcol;
  FILE *file = fopen("test.txt", "r");

  read_file(file, &Maxrow, &Maxcol);
  fclose(file);

  TEST_ASSERT_EQUAL_INT_MESSAGE(5, Maxrow, "read_file Maxrow is not 5.");
  file = NULL;
  int infoback = read_file(file, &Maxrow, &Maxcol);
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1, infoback, "read_file infoback is not -1.");
}
void test_write_file()
{
  unsigned int Maxrow = 5;
  unsigned int Maxcol = 5;
  FILE *file = fopen("testw.txt", "w");
  int **map = create_map(&Maxrow, &Maxcol);
  map[0][1] = 1;
  write_file(file, &Maxrow, &Maxcol, map);
  fclose(file);
  file = fopen("testw.txt", "r");
  read_file(file, &Maxrow, &Maxcol);
  fclose(file);
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, map[0][1], "wrote_file wrong.");
}

void setUp()
{
}
void tearDown()
{
}

int main()
{
  UNITY_BEGIN();
  RUN_TEST(test_create_map);
  RUN_TEST(test_check_next);
  RUN_TEST(test_insert_map);
  RUN_TEST(test_read_file);
  RUN_TEST(test_write_file);

  return UNITY_END();
}
