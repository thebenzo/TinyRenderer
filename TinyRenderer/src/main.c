#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

bool isRunning = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int windowWidth = 1280;
int windowHeight = 800;

uint32_t* colorBuffer = NULL;

SDL_Texture* texture = NULL;

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

void Setup()
{
	colorBuffer = (uint32_t*)malloc(windowWidth * windowHeight * sizeof(uint32_t));

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
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

void DrawGrid(int gridSize)
{
	for (int y = 0; y < windowHeight; y++)
	{
		for (int x = 0; x < windowWidth; x++)
		{
			if (x % gridSize == 0 || y % gridSize == 0)
			{
				colorBuffer[(y * windowWidth) + x] = 0xFF999999;
			}
		}
	}
}

void DrawDotGrid(int gridSize)
{
	for (int y = 0; y < windowHeight; y += gridSize)
	{
		for (int x = 0; x < windowWidth; x += gridSize)
		{
			colorBuffer[(y * windowWidth) + x] = 0xFF999999;
		}
	}
}

void DrawRect(int x, int y, int width, int height, uint32_t color)
{
	for (int i = y; i < (y + height); i++)
	{
		for (int j = x; j < (x + width); j++)
		{
			colorBuffer[(i * windowWidth) + j] = color;
		}
	}
}

void ProcessInputs()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Render()
{
	SDL_SetRenderDrawColor(renderer, 218, 247, 166, 255);
	SDL_RenderClear(renderer);

	DrawDotGrid(10);
	DrawRect(200, 200, 200, 100, 0xFF00FF00);

	RenderColorBuffer();
	ClearColorBuffer(0xFF1E1E1E);

	SDL_RenderPresent(renderer);
}

void Destroy()
{
	free(colorBuffer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	isRunning = InitializeWindow();

	Setup();

	while (isRunning)
	{
		ProcessInputs();
		Render();
	}

	Destroy();

	return 0;
}
