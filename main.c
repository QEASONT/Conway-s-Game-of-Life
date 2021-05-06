#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include "read_write.h"
#include "lifegame.h"

//Screen dimension constants
int main(int argc, char *argv[])
{
    unsigned int Maxrow;
    unsigned int Maxcol;
    char row_str[100];
    char col_str[100];
    FILE *file;
    FILE *filer;
    int PX;
    char option[10];
    int x_get = 0;
    int times;
    int y_get = 0;
    int row = 0;
    int col = 0;
    int drag = 0;
    int count = 0;

    printf("Welcome to Game of Life!\n");
    printf("Please choose an option:\n");
    printf("(1) Read the exist file.\n");
    printf("(2) Customization.\n");
    printf("(3) Quit.\n");
    printf("  Option: ");
    memset(option, 0, 10 * sizeof(char));
    fgets(option, 10, stdin);
    if (strlen(option) != sizeof(option) - 1)
        option[strlen(option) - 1] = '\0';
    while (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0)
    {
        printf("\n");
        printf("Sorry, the option you entered was invalid.\n");
        printf("\n");
        printf("Please choose an option:\n");
        printf("(1) Read the exit file.\n");
        printf("(2) Customization.\n");
        printf("(3) Quit.\n");
        printf("  Option: ");
        memset(option, 0, 10 * sizeof(char));
        fgets(option, 10, stdin);
        if (strlen(option) != sizeof(option) - 1)
            option[strlen(option) - 1] = '\0';
        if (strcmp(option, "3") == 0)
        {
            goto END;
        }
    }
    if (strcmp(option, "1") == 0)
    {
        file = fopen("test.txt", "r");
        if (file == NULL)
        {
            printf("no file to store.\n");
            goto END;
        }

        read_file(file, &Maxrow, &Maxcol);
        int **map = create_map(&Maxrow, &Maxcol);
        fclose(file);
        file = fopen("test.txt", "r");
        insert_map(file, &Maxrow, &Maxcol, map);
        fclose(file);
        if (max_Fun(Maxcol, Maxrow) < 10)
        {
            PX = 250 / max_Fun(Maxcol, Maxrow);
        }
        else if (max_Fun(Maxcol, Maxrow) < 50)
        {
            PX = 500 / max_Fun(Maxcol, Maxrow);
        }
        else if (max_Fun(Maxcol, Maxrow) < 100)
        {
            PX = 600 / max_Fun(Maxcol, Maxrow);
        }
        else if (max_Fun(Maxcol, Maxrow) < 500)
        {
            PX = 800 / max_Fun(Maxcol, Maxrow);
        }
        else
        {
            PX = 1000 / max_Fun(Maxcol, Maxrow);
        }

        //初始化sdl
        SDL_Init(SDL_INIT_EVERYTHING);
        //创建窗口
        SDL_Window *win = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Maxcol * PX, Maxrow * PX, SDL_WINDOW_SHOWN);
        //创建一个渲染器
        SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        SDL_SetRenderDrawColor(ren, 225, 255, 225, 225);

        /* Clear the entire screen to our selected color. */
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 225);
        for (int i = 0; i < Maxrow; i++)
        {
            //绘制直线
            SDL_RenderDrawLine(ren, 0, i * PX, Maxcol * PX, i * PX);
        }
        for (int i = 0; i < Maxcol; i++)
        {
            //绘制直线
            SDL_RenderDrawLine(ren, i * PX, 0, i * PX, Maxrow * PX);
        }

        // 创建一个矩形
        for (int i = 0; i < Maxrow; i++)
        {
            for (int j = 0; j < Maxcol; j++)
            {
                if (map[i][j] == 1)
                {
                    SDL_Rect rect1 = {j * PX, i * PX, PX, PX};
                    //设置渲染颜色
                    SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
                    //绘制线框矩形
                    SDL_RenderFillRect(ren, &rect1);
                }
            }
        }

        // //设置渲染颜色
        // SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
        // //绘制线框矩形
        // SDL_RenderDrawRect(ren, &rect1);

        //更新屏幕
        SDL_RenderPresent(ren);
        int quit = 0;    //退出
        SDL_Event event; //监听退出活动

        while (!quit)
        { //主消息循环
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            //用户从菜单要求退出程序
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (SDL_BUTTON_LEFT == event.button.button)
                {

                    check_next(&Maxrow, &Maxcol, map);
                    SDL_SetRenderDrawColor(ren, 225, 255, 225, 225);

                    /* Clear the entire screen to our selected color. */
                    SDL_RenderClear(ren);

                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 225);
                    for (int i = 0; i < Maxrow; i++)
                    {
                        //绘制直线
                        SDL_RenderDrawLine(ren, 0, i * PX, Maxcol * PX, i * PX);
                    }
                    for (int i = 0; i < Maxcol; i++)
                    {
                        //绘制直线
                        SDL_RenderDrawLine(ren, i * PX, 0, i * PX, Maxrow * PX);
                    }
                    // 创建一个矩形
                    for (int i = 0; i < Maxrow; i++)
                    {
                        for (int j = 0; j < Maxcol; j++)
                        {
                            if (map[i][j] == 1)
                            {
                                SDL_Rect rect1 = {j * PX, i * PX, PX, PX};
                                //设置渲染颜色
                                SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
                                //绘制线框矩形
                                SDL_RenderFillRect(ren, &rect1);
                            }
                        }
                    }

                    SDL_RenderPresent(ren);
                }
                if (SDL_BUTTON_RIGHT == event.button.button)
                {
                    count = 0;
                    while (check_same(&Maxrow, &Maxcol, map) == 0 && count < 200)
                    {
                        count++;
                        check_next(&Maxrow, &Maxcol, map);
                        SDL_SetRenderDrawColor(ren, 225, 255, 225, 225);

                        /* Clear the entire screen to our selected color. */
                        SDL_RenderClear(ren);

                        SDL_SetRenderDrawColor(ren, 0, 0, 0, 225);
                        for (int i = 0; i < Maxrow; i++)
                        {
                            //绘制直线
                            SDL_RenderDrawLine(ren, 0, i * PX, Maxcol * PX, i * PX);
                        }
                        for (int i = 0; i < Maxcol; i++)
                        {
                            //绘制直线
                            SDL_RenderDrawLine(ren, i * PX, 0, i * PX, Maxrow * PX);
                        }
                        // 创建一个矩形
                        for (int i = 0; i < Maxrow; i++)
                        {
                            for (int j = 0; j < Maxcol; j++)
                            {
                                if (map[i][j] == 1)
                                {
                                    SDL_Rect rect1 = {j * PX, i * PX, PX, PX};
                                    //设置渲染颜色
                                    SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
                                    //绘制线框矩形
                                    SDL_RenderFillRect(ren, &rect1);
                                }
                            }
                        }

                        SDL_RenderPresent(ren);
                        SDL_Delay(500);
                    }
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_1:
                    times = 1;
                    break;
                case SDLK_2:
                    times = 2;
                    break;
                case SDLK_3:
                    times = 3;
                    break;
                case SDLK_4:
                    times = 4;
                    break;
                case SDLK_5:
                    times = 5;
                    break;
                case SDLK_6:
                    times = 6;
                    break;
                case SDLK_7:
                    times = 7;
                    break;
                case SDLK_8:
                    times = 8;
                    break;
                case SDLK_9:
                    times = 9;
                    break;
                case SDLK_s:
                    file = fopen("test.txt", "w");
                    write_file(file, &Maxrow, &Maxcol, map);
                    fclose(file);
                    quit = 1;
                    break;
                }
                for (int i = 0; i < times; i++)
                {
                    check_next(&Maxrow, &Maxcol, map);
                    SDL_SetRenderDrawColor(ren, 225, 255, 225, 225);

                    /* Clear the entire screen to our selected color. */
                    SDL_RenderClear(ren);

                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 225);
                    for (int i = 0; i < Maxrow; i++)
                    {
                        //绘制直线
                        SDL_RenderDrawLine(ren, 0, i * PX, Maxcol * PX, i * PX);
                    }
                    for (int i = 0; i < Maxcol; i++)
                    {
                        //绘制直线
                        SDL_RenderDrawLine(ren, i * PX, 0, i * PX, Maxrow * PX);
                    }
                    // 创建一个矩形
                    for (int i = 0; i < Maxrow; i++)
                    {
                        for (int j = 0; j < Maxcol; j++)
                        {
                            if (map[i][j] == 1)
                            {
                                SDL_Rect rect1 = {j * PX, i * PX, PX, PX};
                                //设置渲染颜色
                                SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
                                //绘制线框矩形
                                SDL_RenderFillRect(ren, &rect1);
                            }
                        }
                    }

                    SDL_RenderPresent(ren);
                    SDL_Delay(300);
                }
                times = 0;
            }
        }
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        for (int i = 0; i < (Maxrow); ++i)
        {
            free(map[i]);
        }
        free(map);
    }
    else if (strcmp(option, "2") == 0)
    {
    INPUTNUM:
        printf("Please input the number of row: ");
        memset(row_str, 0, sizeof(row_str));
        fgets(row_str, 100, stdin);
        if (strlen(row_str) != sizeof(row_str) - 1)
            row_str[strlen(row_str) - 1] = '\0';
        fflush(stdin);
        while (isalldigit(row_str) == 0)
        {
            memset(row_str, 0, sizeof(row_str));
            printf("Please input the correct number of row: ");
            fgets(row_str, 100, stdin);
            if (strlen(row_str) != sizeof(row_str) - 1)
                row_str[strlen(row_str) - 1] = '\0';
            fflush(stdin);
        }
        Maxrow = strtoul(row_str, NULL, 10);

        printf("Please input the number of col: ");
        memset(col_str, 0, sizeof(col_str));
        fgets(col_str, 100, stdin);
        if (strlen(col_str) != sizeof(col_str) - 1)
            col_str[strlen(col_str) - 1] = '\0';
        fflush(stdin);
        while (isalldigit(col_str) == 0)
        {
            printf("Please input the correct number of col: ");
            memset(col_str, 0, sizeof(col_str));
            fgets(col_str, 100, stdin);
            if (strlen(col_str) != sizeof(col_str) - 1)
                col_str[strlen(col_str) - 1] = '\0';
            fflush(stdin);
        }
        Maxcol = strtoul(col_str, NULL, 10);
        if (Maxcol > 501 || Maxrow > 501)
        {
            printf("the number of row and col shouldn't bigger than 500.\n");
            goto INPUTNUM;
        }

        if (max_Fun(Maxcol, Maxrow) < 10)
        {
            PX = 250 / max_Fun(Maxcol, Maxrow);
        }
        else if (max_Fun(Maxcol, Maxrow) < 50)
        {
            PX = 500 / max_Fun(Maxcol, Maxrow);
        }
        else if (max_Fun(Maxcol, Maxrow) < 100)
        {
            PX = 600 / max_Fun(Maxcol, Maxrow);
        }
        else if (max_Fun(Maxcol, Maxrow) < 500)
        {
            PX = 800 / max_Fun(Maxcol, Maxrow);
        }
        else
        {
            PX = 1000 / max_Fun(Maxcol, Maxrow);
        }
        int **map = create_map(&Maxrow, &Maxcol);
        //初始化sdl
        SDL_Init(SDL_INIT_EVERYTHING);
        //创建窗口
        SDL_Window *win = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Maxcol * PX, Maxrow * PX, SDL_WINDOW_SHOWN);
        //创建一个渲染器
        SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        SDL_SetRenderDrawColor(ren, 225, 255, 225, 225);

        /* Clear the entire screen to our selected color. */
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 225);
        for (int i = 0; i < Maxrow; i++)
        {
            //绘制直线
            SDL_RenderDrawLine(ren, 0, i * PX, Maxcol * PX, i * PX);
        }
        for (int i = 0; i < Maxcol; i++)
        {
            //绘制直线
            SDL_RenderDrawLine(ren, i * PX, 0, i * PX, Maxrow * PX);
        }

        // 创建一个矩形
        for (int i = 0; i < Maxrow; i++)
        {
            for (int j = 0; j < Maxcol; j++)
            {
                if (map[i][j] == 1)
                {
                    SDL_Rect rect1 = {j * PX, i * PX, PX, PX};
                    //设置渲染颜色
                    SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
                    //绘制线框矩形
                    SDL_RenderFillRect(ren, &rect1);
                }
            }
        }

        // //设置渲染颜色
        // SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
        // //绘制线框矩形
        // SDL_RenderDrawRect(ren, &rect1);

        //更新屏幕
        SDL_RenderPresent(ren);
        int quit = 0;
        SDL_Event event;
        while (!quit)
        { //主消息循环
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            //用户从菜单要求退出程序
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_MOUSEMOTION:
                if (drag == 1)
                {
                    x_get = event.button.x;
                    y_get = event.button.y;
                    int int_x = (int)x_get;
                    int int_y = (int)y_get;
                    int int_px = (int)PX;
                    row = int_y / int_px;
                    col = int_x / int_px;
                    map[row][col] = 1;
                    SDL_SetRenderDrawColor(ren, 225, 255, 225, 225);

                    /* Clear the entire screen to our selected color. */
                    SDL_RenderClear(ren);

                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 225);
                    for (int i = 0; i < Maxrow; i++)
                    {
                        //绘制直线
                        SDL_RenderDrawLine(ren, 0, i * PX, Maxcol * PX, i * PX);
                    }
                    for (int i = 0; i < Maxcol; i++)
                    {
                        //绘制直线
                        SDL_RenderDrawLine(ren, i * PX, 0, i * PX, Maxrow * PX);
                    }
                    // 创建一个矩形
                    for (int i = 0; i < Maxrow; i++)
                    {
                        for (int j = 0; j < Maxcol; j++)
                        {
                            if (map[i][j] == 1)
                            {
                                SDL_Rect rect1 = {j * PX, i * PX, PX, PX};
                                //设置渲染颜色
                                SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
                                //绘制线框矩形
                                SDL_RenderFillRect(ren, &rect1);
                            }
                        }
                    }

                    SDL_RenderPresent(ren);
                }

                break;
            case SDL_MOUSEBUTTONDOWN:
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    drag = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (SDL_BUTTON_LEFT == event.button.button)
                {
                    drag = 0;
                }
                break;
            case SDL_KEYDOWN:
                if (SDLK_RETURN == event.key.keysym.sym)
                {
                    check_next(&Maxrow, &Maxcol, map);
                    SDL_SetRenderDrawColor(ren, 225, 255, 225, 225);

                    /* Clear the entire screen to our selected color. */
                    SDL_RenderClear(ren);

                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 225);
                    for (int i = 0; i < Maxrow; i++)
                    {
                        //绘制直线
                        SDL_RenderDrawLine(ren, 0, i * PX, Maxcol * PX, i * PX);
                    }
                    for (int i = 0; i < Maxcol; i++)
                    {
                        //绘制直线
                        SDL_RenderDrawLine(ren, i * PX, 0, i * PX, Maxrow * PX);
                    }
                    // 创建一个矩形
                    for (int i = 0; i < Maxrow; i++)
                    {
                        for (int j = 0; j < Maxcol; j++)
                        {
                            if (map[i][j] == 1)
                            {
                                SDL_Rect rect1 = {j * PX, i * PX, PX, PX};
                                //设置渲染颜色
                                SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
                                //绘制线框矩形
                                SDL_RenderFillRect(ren, &rect1);
                            }
                        }
                    }

                    SDL_RenderPresent(ren);
                }
                if (SDLK_g == event.key.keysym.sym)
                {
                    count = 0;
                    while (check_same(&Maxrow, &Maxcol, map) == 0 && count < 200)
                    {
                        count++;
                        check_next(&Maxrow, &Maxcol, map);
                        SDL_SetRenderDrawColor(ren, 225, 255, 225, 225);

                        /* Clear the entire screen to our selected color. */
                        SDL_RenderClear(ren);

                        SDL_SetRenderDrawColor(ren, 0, 0, 0, 225);
                        for (int i = 0; i < Maxrow; i++)
                        {
                            //绘制直线
                            SDL_RenderDrawLine(ren, 0, i * PX, Maxcol * PX, i * PX);
                        }
                        for (int i = 0; i < Maxcol; i++)
                        {
                            //绘制直线
                            SDL_RenderDrawLine(ren, i * PX, 0, i * PX, Maxrow * PX);
                        }
                        // 创建一个矩形
                        for (int i = 0; i < Maxrow; i++)
                        {
                            for (int j = 0; j < Maxcol; j++)
                            {
                                if (map[i][j] == 1)
                                {
                                    SDL_Rect rect1 = {j * PX, i * PX, PX, PX};
                                    //设置渲染颜色
                                    SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
                                    //绘制线框矩形
                                    SDL_RenderFillRect(ren, &rect1);
                                }
                            }
                        }

                        SDL_RenderPresent(ren);
                        SDL_Delay(300);
                    }
                }
                if (event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_5 || event.key.keysym.sym == SDLK_6 | event.key.keysym.sym == SDLK_7 || event.key.keysym.sym == SDLK_8 || event.key.keysym.sym == SDLK_9)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_1:
                        times = 1;
                        break;
                    case SDLK_2:
                        times = 2;
                        break;
                    case SDLK_3:
                        times = 3;
                        break;
                    case SDLK_4:
                        times = 4;
                        break;
                    case SDLK_5:
                        times = 5;
                        break;
                    case SDLK_6:
                        times = 6;
                        break;
                    case SDLK_7:
                        times = 7;
                        break;
                    case SDLK_8:
                        times = 8;
                        break;
                    case SDLK_9:
                        times = 9;
                        break;
                    }
                    for (int i = 0; i < times; i++)
                    {
                        check_next(&Maxrow, &Maxcol, map);
                        SDL_SetRenderDrawColor(ren, 225, 255, 225, 225);

                        /* Clear the entire screen to our selected color. */
                        SDL_RenderClear(ren);

                        SDL_SetRenderDrawColor(ren, 0, 0, 0, 225);
                        for (int i = 0; i < Maxrow; i++)
                        {
                            //绘制直线
                            SDL_RenderDrawLine(ren, 0, i * PX, Maxcol * PX, i * PX);
                        }
                        for (int i = 0; i < Maxcol; i++)
                        {
                            //绘制直线
                            SDL_RenderDrawLine(ren, i * PX, 0, i * PX, Maxrow * PX);
                        }
                        // 创建一个矩形
                        for (int i = 0; i < Maxrow; i++)
                        {
                            for (int j = 0; j < Maxcol; j++)
                            {
                                if (map[i][j] == 1)
                                {
                                    SDL_Rect rect1 = {j * PX, i * PX, PX, PX};
                                    //设置渲染颜色
                                    SDL_SetRenderDrawColor(ren, 0, 0, 225, 225);
                                    //绘制线框矩形
                                    SDL_RenderFillRect(ren, &rect1);
                                }
                            }
                        }

                        SDL_RenderPresent(ren);
                        SDL_Delay(500);
                    }
                    times = 0;
                }
                if (SDLK_s == event.key.keysym.sym)
                {
                    file = fopen("test.txt", "w");
                    if (file == NULL)
                    {
                        printf("no file to store.\n");
                    }
                    else
                    {
                        write_file(file, &Maxrow, &Maxcol, map);
                        fclose(file);
                        quit = 1;
                    }
                }
                break;
            }
        }
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        for (int i = 0; i < (Maxrow); ++i)
        {
            free(map[i]);
        }
        free(map);
    }
END:
    printf("Thanks for using.\n");
    return 0;
}
