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

    char buf[MAX_LINE];
    memset(buf, 0, sizeof(buf));
    int len = 0;
    if (file == NULL)
    {
        return 1;
    }
    while (fgets(buf, MAX_LINE, file) != NULL)
    {
        (*pMaxrow)++;
        len = strspn(buf, "0123456789");
        // if (buf[len - 1] == '\n')
        // {
        //     buf[len - 1] = '\0';
        // }
        // len = strlen(buf);
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
int write_file(FILE *file, unsigned int *pMaxrow,
              unsigned int *pMaxcol, int **map)
{
    char buf[MAX_LINE];
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
int main(void)
{
    char option[10];
    unsigned int Maxrow;
    unsigned int Maxcol;
    FILE *file = fopen("test.txt", "r");
    FILE *filer = fopen("test1.txt", "w");

    read_file(file, &Maxrow, &Maxcol);
    int **map = create_map(&Maxrow, &Maxcol);
    fclose(file);
    file = fopen("test.txt", "r");
    insert_map(file, &Maxrow, &Maxcol, map);
    fclose(file);
    memset(option, 0, 10 * sizeof(char));
    fgets(option, 10, stdin);
    if (strlen(option) != sizeof(option) - 1)
        option[strlen(option) - 1] = '\0';
    for (int i = 0; i < (Maxrow); ++i)
    {
        for (int j = 0; j < (Maxcol); ++j)
        {
            printf("%d", map[i][j]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    while (1)
    {
        while (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0 && strcmp(option, "4") != 0 && strcmp(option, "5") != 0)
        {
            printf("\n");
            printf("Sorry, the option you entered was invalid.\n");
            printf("\n");

            memset(option, 0, 10 * sizeof(char));
            fgets(option, 10, stdin);
            if (strlen(option) != sizeof(option) - 1)
                option[strlen(option) - 1] = '\0';
            if (strcmp(option, "5") == 0)
            {
                break;
            }
        }
        if (strcmp(option, "5") == 0)
        {
            printf("Thanks for using.\n");
            break;
        }
        if (strcmp(option, "1") == 0)
        {
            check_next(&Maxrow, &Maxcol, map);
            for (int i = 0; i < (Maxrow); ++i)
            {
                for (int j = 0; j < (Maxcol); ++j)
                {
                    printf("%d", map[i][j]);
                    printf(" ");
                }
                printf("\n");
            }
        }
        if (strcmp(option, "2") == 0)
        {
            write_file(filer, &Maxrow, &Maxcol, map);
            fclose(filer);
        }
        printf("\n");
        memset(option, 0, 10 * sizeof(char));
        fgets(option, 10, stdin);
        if (strlen(option) != sizeof(option) - 1)
            option[strlen(option) - 1] = '\0';
    }

    return 0;
}
