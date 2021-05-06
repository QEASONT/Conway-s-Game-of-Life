#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_write.h"

// return the map
int **create_map(const unsigned int *pMaxrow,
                 const unsigned int *pMaxcol);
int check_next(const unsigned int *pMaxrow,
               const unsigned int *pMaxcol, int **map);

int insert_map(FILE *file, const unsigned int *pMaxrow,
               const unsigned int *pMaxcol, int **map);

int check_same(const unsigned int *pMaxrow,
               const unsigned int *pMaxcol, int **map);
int isalldigit(char *str);
unsigned int max_Fun(unsigned int x,unsigned int y);