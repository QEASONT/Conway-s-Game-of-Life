#include<stdio.h>
#include<SDL2/SDL.h>
int main(int argc, char* argv[])//C语言完整格式
{
	
	if(SDL_Init(SDL_INIT_VIDEO) == -1){	//SDL_初始化
		printf("Could not initialize SDL!\n");
		return 0;
	}
	printf("SDL initialized.\n");
	
	//创建窗口
	SDL_Window *win = SDL_CreateWindow("Hello World!",
			 0, SDL_WINDOWPOS_CENTERED,
			 300, 300, SDL_WINDOW_SHOWN);
	//创建渲染器
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
			 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	//创建表面
	SDL_Surface *temp_Surface = SDL_LoadBMP("llllll.bmp");	
	
	if(win == NULL || ren == NULL || temp_Surface == NULL)
		printf("%s\n",SDL_GetError());
	
    //创建材质
    SDL_Texture *tex = NULL;
    tex = SDL_CreateTextureFromSurface(ren, temp_Surface);
    //清空渲染器
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    //将材质复制到渲染器
    SDL_RenderCopy(ren, tex, NULL, NULL);
    //呈现渲染器
    SDL_RenderPresent(ren);
	
	int quit = 0;//退出
	SDL_Event event;//监听退出活动
	
	while (!quit)
	{//主消息循环
		SDL_WaitEvent(&event);
		switch (event.type)
		{   
			//用户从菜单要求退出程序
			case SDL_QUIT:
				quit = 1;
				break;
		}
	}
	
	//清理资源
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(temp_Surface);
	SDL_DestroyRenderer(ren);
	if(SDL_GetError())
		printf("%s\n",SDL_GetError());
	SDL_Quit();	//退出SDL调用
	
	return 0;
}

