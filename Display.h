#ifndef DISPLAY_BY_CK
#define DISPLAY_BY_CK
#include<SDL.h>
#include "Screen.h"
#include <windows.h>
#include<vector>
#include "Color.h"
class Display
{
public:
	Display(Screen screen)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			MessageBox(0, L"SDL≥ı ºªØ ß∞‹", 0, 0);
			exit(0);
		}
		mScreen = screen;
		mpWindow = SDL_CreateWindow(
			"SoftRasterizer",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			static_cast<int>(screen.width),
			static_cast<int>(screen.height), 0);

		mpSurface = SDL_GetWindowSurface(mpWindow);
	}
	~Display()
	{
		SDL_DestroyWindow(mpWindow);
		SDL_FreeSurface(mpSurface);
		SDL_Quit();
	}
	void Present(const std::vector<Math::Color>& color)
	{
		auto data = reinterpret_cast<uint32_t*>(mpSurface->pixels);
		int i = 0;
		for (UINT i = 0; i < color.size(); ++i)
		{
			auto colorU32 = color[i];
			data[i] = *(reinterpret_cast<uint32_t*>(&colorU32));
		}
		SDL_UpdateWindowSurface(mpWindow);
	}

private:
	Screen mScreen;
	SDL_Window* mpWindow;
	SDL_Surface* mpSurface;
};

#endif
