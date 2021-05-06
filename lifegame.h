#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_write.h"

// create a two dimension int map to save the cell 
int **create_map(const unsigned int *pMaxrow,
                 const unsigned int *pMaxcol);
// calculate the next statement
int check_next(const unsigned int *pMaxrow,
               const unsigned int *pMaxcol, int **map);
// read cells from file and insert into map 
int insert_map(FILE *file, const unsigned int *pMaxrow,
               const unsigned int *pMaxcol, int **map);
// check whether cells change in next statement or not
int check_same(const unsigned int *pMaxrow,
               const unsigned int *pMaxcol, int **map);
// check whether the string is consist of all digit
int isalldigit(char *str);
// return the larger one between x and y
unsigned int max_Fun(unsigned int x,unsigned int y);