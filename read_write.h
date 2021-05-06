#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_LIMIT 1024

// read information from file
// success return 0 else 1
int read_file(FILE *file, unsigned int *pMaxrow,
              unsigned int *pMaxcol);
// write information into file
int write_file(FILE *file, const unsigned int *pMaxrow,
              const unsigned int *pMaxcol, int **map);
