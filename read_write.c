#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_write.h"
#include "lifegame.h"

int read_file(FILE *file, unsigned int *pMaxrow,
              unsigned int *pMaxcol)
{

    
    *pMaxcol = 0;
    *pMaxrow = 0;

    char buf[BUFFER_LIMIT];
    memset(buf, 0, sizeof(buf));
    int len = 0;
    if (file == NULL)
    {
        return -1;
    }
    while (fgets(buf, BUFFER_LIMIT, file) != NULL)
    {
        (*pMaxrow)++;
        len = strspn(buf, "0123456789");

        if ((*pMaxrow) != 1)
        {
            if ((*pMaxcol) != len)
            {
                return 2;
            }
        }
        else
        {
            (*pMaxcol) = len;
        }
    }
    return 0;
}
int write_file(FILE *file, const unsigned int *pMaxrow,
              const unsigned int *pMaxcol, int **map)
{
    char buf[BUFFER_LIMIT];
    memset(buf, 0, sizeof(buf));
    int len = 0;
    if (file == NULL)
    {
        return 1;
    }
    for (int i = 0; i < (*pMaxrow); i++)
    {
        for (int j = 0; j < (*pMaxcol); j++)
        {
            buf[j]= map[i][j]  + '0';
        }
        len = strlen(buf);
        if (i==0)
        {
            buf[len]= '\n';
        }
        fputs(buf,file);
        
    }
    
    return 0;
}