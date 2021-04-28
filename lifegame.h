#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_write.h"

// return the map
int **create_map(unsigned int *pMaxrow,
                 unsigned int *pMaxcol);
int check_next(unsigned int *pMaxrow,
               unsigned int *pMaxcol, int **map);

int insert_map(FILE *file, unsigned int *pMaxrow,
               unsigned int *pMaxcol, int **map);

int check_same(unsigned int *pMaxrow,
               unsigned int *pMaxcol, int **map);
int isalldigit(char *str);
unsigned int max_Fun(unsigned int x,unsigned int y);