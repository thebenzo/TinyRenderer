#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern int windowWidth;
extern int windowHeight;

extern uint32_t* colorBuffer;

extern SDL_Texture* texture;

bool InitializeWindow();
void ClearColorBuffer(uint32_t color);
void RenderColorBuffer();
void DrawGrid(int gridSize);
void DrawDotGrid(int gridSize);
void DrawRect(int x, int y, int width, int height, uint32_t color);
void Destroy();

#endif // !RENDERER_H
