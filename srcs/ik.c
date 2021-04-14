#include "../include/IK.h"

void DrawIk(IK_Chain *chain, SDLX_Display *display)
{
	MT_Vector2 vec;
	MT_Vector2 start;
	int i;

	i = 0;
	start = chain->start;
	while(i < chain->len)
	{
		vec = MT_V2FromAngle_Rad(chain->chain[i].angle, chain->chain[i].length);
		FillCircle(display->renderer, (Circle){start.x ,start.y, 10});
		SDL_RenderDrawLine(display->renderer,
							start.x, start.y, start.x + vec.x , start.y + vec.y);
		i++;
	}

}


