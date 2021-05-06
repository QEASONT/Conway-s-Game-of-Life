#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lifegame.h"

int **create_map(const unsigned int *pMaxrow,
                 const unsigned int *pMaxcol)
{
    int **p = (int **)malloc(sizeof(int *) * (*pMaxrow));
    if ((*pMaxrow) <= 0 || (*pMaxcol) <= 0)
    {
        int **p = NULL;
        return p;
    }
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

int insert_map(FILE *file, const unsigned int *pMaxrow,
               const unsigned int *pMaxcol, int **map)
{
    if (((*pMaxcol) <= 0) || ((*pMaxrow) <= 0))
    {
        return -2;
    }

    if (file == NULL)
    {
        return -1;
    }

    char buf[BUFFER_LIMIT];
    memset(buf, 0, sizeof(buf));
    int len = 0;
    unsigned int col = 0;
    unsigned int row = 0;

    while (fgets(buf, BUFFER_LIMIT, file) != NULL)
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
int check_next(const unsigned int *pMaxrow,
               const unsigned int *pMaxcol, int **map)
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
            if (j - 1 >= 0)
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

int check_same(const unsigned int *pMaxrow,
               const unsigned int *pMaxcol, int **map)
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
            if (j - 1 >= 0)
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
            if (map[i][j] != temp_map[i][j])
            {
                for (int i = 0; i < (*pMaxrow); ++i)
                {
                    free(temp_map[i]);
                }
                free(temp_map);
                return 0;
            }
        }
    }
    for (int i = 0; i < (*pMaxrow); ++i)
    {
        free(temp_map[i]);
    }
    free(temp_map);
    return 1;
}
int isalldigit(char *str)
{
    int len;
    len = strspn(str, "0123456789");
    if (len == strlen(str))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
unsigned int max_Fun(unsigned int x, unsigned int y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}
