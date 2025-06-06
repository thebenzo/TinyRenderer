#include "Renderer.h"

SDL_Window* window = NULL;
extern SDL_Renderer* renderer = NULL;

extern int windowWidth = 1280;
extern int windowHeight = 720;

extern uint32_t* colorBuffer = NULL;

extern SDL_Texture* texture = NULL;

bool InitializeWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Failed to initialize SDL subsystems");
		return false;
	}

	window = SDL_CreateWindow("Tiny Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Failed to create SDL Window");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Failed to create SDL Renderer");
		return false;
	}

	return true;
}

void ClearColorBuffer(uint32_t color)
{
	for (int y = 0; y < windowHeight; y++)
	{
		for (int x = 0; x < windowWidth; x++)
		{
			colorBuffer[(y * windowWidth) + x] = color;
		}
	}
}

void RenderColorBuffer()
{
	SDL_UpdateTexture(texture, NULL, colorBuffer, (int)(windowWidth * sizeof(uint32_t)));
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void DrawPixel(int x, int y, uint32_t color)
{
	if ((x >= 0 && x <= windowWidth) && (y >= 0 && y <= windowHeight))
	{
		colorBuffer[(y * windowWidth) + x] = color;
	}
}

void DrawGrid(int gridSize, uint32_t color)
{
	for (int y = 0; y < windowHeight; y++)
	{
		for (int x = 0; x < windowWidth; x++)
		{
			if (x % gridSize == 0 || y % gridSize == 0)
			{
				DrawPixel(x, y, color);
			}
		}
	}
}

void DrawDotGrid(int gridSize, uint32_t color)
{
	for (int y = 0; y < windowHeight; y += gridSize)
	{
		for (int x = 0; x < windowWidth; x += gridSize)
		{
			DrawPixel(x, y, color);
		}
	}
}

void DrawRect(int x, int y, int width, int height, uint32_t color)
{
	for (int i = y; i < (y + height); i++)
	{
		for (int j = x; j < (x + width); j++)
		{
			DrawPixel(j, i, color);
		}
	}
}

void Destroy()
{
	free(colorBuffer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
