// #include<stdio.h>
// #include<SDL2/SDL.h>
// int main(int argc, char* argv[])//C语言完整格式
// {
	
// 	if(SDL_Init(SDL_INIT_VIDEO) == -1){	//SDL_初始化
// 		printf("Could not initialize SDL!\n");
// 		return 0;
// 	}
// 	printf("SDL initialized.\n");
// 	// 
// 	//创建窗口
// 	SDL_Window *win = SDL_CreateWindow("Hello World!",
// 			 0, SDL_WINDOWPOS_CENTERED,
// 			 300, 300, SDL_WINDOW_SHOWN);
// 	//创建渲染器
// 	SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
// 			 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
// 	//创建表面
// 	SDL_Surface *temp_Surface = SDL_LoadBMP("llllll.bmp");	
	
// 	if(win == NULL || ren == NULL || temp_Surface == NULL)
// 		printf("%s\n",SDL_GetError());
	
//     //创建材质
//     SDL_Texture *tex = NULL;
//     tex = SDL_CreateTextureFromSurface(ren, temp_Surface);
//     //清空渲染器
//     SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
//     SDL_RenderClear(ren);
//     //将材质复制到渲染器
//     SDL_RenderCopy(ren, tex, NULL, NULL);
//     //呈现渲染器
//     SDL_RenderPresent(ren);
	
// 	int quit = 0;//退出
// 	SDL_Event event;//监听退出活动
	
// 	while (!quit)
// 	{//主消息循环
// 		SDL_WaitEvent(&event);
// 		switch (event.type)
// 		{   
// 			//用户从菜单要求退出程序
// 			case SDL_QUIT:
// 				quit = 1;
// 				break;
// 		}
// 	}
	
// 	//清理资源
// 	SDL_DestroyTexture(tex);
// 	SDL_FreeSurface(temp_Surface);
// 	SDL_DestroyRenderer(ren);
// 	if(SDL_GetError())
// 		printf("%s\n",SDL_GetError());
// 	SDL_Quit();	//退出SDL调用
	
// 	return 0;
// }

// // #include <SDL2/SDL.h>
 
// // SDL_Window *window = NULL;
// // SDL_Surface *surface = NULL;
 
// // //main函数中的参数不能省略，不然会报错
// // int main(int args, char *argv[])
// // {
// //     SDL_Init(SDL_INIT_VIDEO);
// //     window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
// //     if (!window)
// //         return -1;
// //     surface = SDL_GetWindowSurface(window);
// //     if (!surface)
// //         return -2;
 
// //     SDL_Rect rec;
// //     rec.x = 700;
// //     rec.y = 10,
// //     rec.w = 20;
// //     rec.h = 20;
 
// //     while (1)
// //     {
// //         SDL_FillRect(surface, &rec, SDL_MapRGB(surface->format, 180, 10, 140));
 
// //         rec.x += 6;
// //         rec.y += 2;
// //         rec.x = rec.x > 800 ? 0 : rec.x;
// //         rec.y = rec.y > 600 ? 0 : rec.y;
 
// //         SDL_FillRect(surface, &rec, SDL_MapRGB(surface->format, 10, 200, 120));
 
// //         SDL_UpdateWindowSurface(window);
// //         SDL_Delay((1.0 / 60) * 1000);
// //     }
// //     SDL_FreeSurface(surface);
// //     SDL_DestroyWindow(window);
// //     SDL_Quit();
 
// //     return 0;
// // }
