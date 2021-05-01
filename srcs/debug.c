#include "IK.h"

void DrawLine(MT_Vector2 slope, double b)
{
    SDLX_Display *display;
    MT_Vector2 p1;
    MT_Vector2 p2;

    p1.x = 0;
    p1.y = (p1.x * slope.x  + b) / slope.y;
    p2.x = WIN_W;
    p2.y = (p2.x * slope.x + b) / slope.y;

    display = SDLX_DisplayGet();
    SDL_SetRenderDrawColor(display->renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(display->renderer, p1.x, p1.y , p2.x, p2.y);
    // SDL_Log()
    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}