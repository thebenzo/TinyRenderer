#include "Renderer.h"
#include "Vector.h"

#define POINTS_COUNT 11 * 11 * 11

bool isRunning = false;

float fov = 128.0f;

Vector3f cubePoints[POINTS_COUNT];
Vector2f projectedCubePoints[POINTS_COUNT];

Vector2f OrthograhicProject(Vector3f point)
{
	Vector2f projectedPoint = { point.x * fov, point.y * fov};
	return projectedPoint;
}

void Setup()
{
	colorBuffer = (uint32_t*)malloc(windowWidth * windowHeight * sizeof(uint32_t));

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

	int pointCount = 0;
	for (float x = -1; x <= 1; x += 0.20f)
	{
		for (float y = -1; y <= 1; y += 0.20f)
		{
			for (float z = -1; z <= 1; z += 0.20f)
			{
				Vector3f point = { x, y, z };
				cubePoints[pointCount++] = point;
			}
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

void Update()
{
	for (int i = 0; i < POINTS_COUNT; i++)
	{
		projectedCubePoints[i] = OrthograhicProject(cubePoints[i]);
	}
}

void Render()
{
	DrawDotGrid(10, 0xFF444444);
	
	for (int i = 0; i < POINTS_COUNT; i++)
	{
		DrawRect(projectedCubePoints[i].x + (windowWidth / 2), projectedCubePoints[i].y + (windowHeight / 2), 5, 5, 0xFF00FF00);
	}

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
		Update();
		Render();
	}

	Destroy();

	return 0;
}
