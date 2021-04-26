#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lifegame.h"
int **create_map(unsigned int *pMaxrow,
                 unsigned int *pMaxcol)
{
    int **p = (int **)malloc(sizeof(int *) * (*pMaxrow));
    for (int i = 0; i < (*pMaxrow); ++i)
    {
        p[i] = (int *)malloc(sizeof(int) * (*pMaxcol));
    }
    for (int i = 0; i < (*pMaxrow); ++i)
    {
        for (int j = 0; j < (*pMaxcol); ++j)
        {
            p[i][j] = 0;
        }
    }

    return p;
}

int insert_map(FILE *file, unsigned int *pMaxrow,
               unsigned int *pMaxcol, int **map)
{
    char buf[MAX_LINE];
    memset(buf, 0, sizeof(buf));
    int len = 0;
    unsigned int col = 0;
    unsigned int row = 0;

    while (fgets(buf, MAX_LINE, file) != NULL)
    {

        len = strspn(buf, "0123456789");

        // if ((buf[len-1]=='\n')||(buf[len-1]=='\r'))
        // {
        //     buf[len - 1] = '\0';
        // }
        // len = strlen(buf);
        for (int i = 0; i < len; i++)
        {
            map[row][col] = buf[i] - '0';
            // printf("%d  ",map[row][col]);
            // printf("%c\n",buf[i]);
            col++;
        }
        col = 0;
        row++;
    }
    return 0;
}
int check_next(unsigned int *pMaxrow,
               unsigned int *pMaxcol, int **map)
{
    int count = 0;
    int **temp_map = create_map(pMaxrow, pMaxcol);
    for (int i = 0; i < (*pMaxrow); ++i)
    {
        for (int j = 0; j < (*pMaxcol); ++j)
        {

            int count = 0;
            if (i - 1 >= 0)
            {
                if (map[i - 1][j] == 1)
                {
                    count++;
                }
            }
            if (i + 1 < (*pMaxrow))
            {
                if (map[i + 1][j] == 1)
                {
                    count++;
                }
            }
            if (j - 1 >=0)
            {
                if (map[i][j - 1] == 1)
                {
                    count++;
                }
            }
            if (j + 1 < (*pMaxcol))
            {
                if (map[i][j + 1] == 1)
                {
                    count++;
                }
            }
            if ((i - 1 >= 0) && (j - 1 >= 0))
            {
                if (map[i - 1][j - 1] == 1)
                {
                    count++;
                }
            }
            if ((i - 1 >= 0) && (j + 1 < (*pMaxcol)))
            {
                if (map[i - 1][j + 1] == 1)
                {
                    count++;
                }
            }

            if ((i + 1 < (*pMaxrow)) && (j + 1 < (*pMaxcol)))
            {
                if (map[i + 1][j + 1] == 1)
                {
                    count++;
                }
            }
            if ((i + 1 < (*pMaxrow)) && (j - 1 >= 0))
            {
                if (map[i + 1][j - 1] == 1)
                {
                    count++;
                }
            }
            if (map[i][j] == 1)
            {
                if (count == 2 || count == 3)
                {
                    temp_map[i][j] = 1;
                }
                else
                {
                    temp_map[i][j] = 0;
                }
            }
            else
            {
                if (count == 3)
                {
                    temp_map[i][j] = 1;
                }
            }
        }
    }
    for (int i = 0; i < (*pMaxrow); ++i)
    {
        for (int j = 0; j < (*pMaxcol); ++j)
        {
            map[i][j] = temp_map[i][j];
        }
    }
    for (int i = 0; i < (*pMaxrow); ++i)
    {
        free(temp_map[i]);
    }
    free(temp_map);
    return 0;
}
