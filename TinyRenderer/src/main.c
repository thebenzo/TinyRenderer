#include "Renderer.h"

bool isRunning = false;

void Setup()
{
	colorBuffer = (uint32_t*)malloc(windowWidth * windowHeight * sizeof(uint32_t));

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
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
