#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

bool isRunning = false;

SDL_Renderer* renderer = NULL;

bool InitializeWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Failed to initialize SDL subsystems");
		return false;
	}

	SDL_Window* window = SDL_CreateWindow("Tiny Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
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

	SDL_RenderPresent(renderer);
}

int main()
{
	isRunning = InitializeWindow();

	while (isRunning)
	{
		ProcessInputs();
		Render();
	}

	return 0;
}
