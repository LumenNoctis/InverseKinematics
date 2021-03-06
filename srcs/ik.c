#include "IK.h"

int CalcAngle(IK_Chain *chain, MT_Vector2 mouse, MT_Vector2 endPoint)// flags bad, but how else..?
{
	int i;
	MT_Vector2	pos_to_mouse;
	MT_Vector2	pos_to_end;
	MT_Vector2	position;
	MT_Vector2	v_corrected;
	double		a_ptm;
	double		a_pte;
	double		angle;

	MT_Vector2 dvec;

	i = chain->len - 1;
	position = endPoint;
	v_corrected = position;
	while (i >= 0)
	{
		if (MT_GetDistance2D(mouse, endPoint) <= MIN_DIST)
			return 1;

		position.x -= chain->chain[i].vec.x;
		position.y -= chain->chain[i].vec.y;

		pos_to_end.x = position.x - endPoint.x;
		pos_to_end.y = position.y - endPoint.y;
		pos_to_mouse.x = position.x - mouse.x;
		pos_to_mouse.y = position.y - mouse.y;
		
		
		a_ptm = MT_V2Heading180_Deg(pos_to_mouse);
		a_pte = MT_V2Heading180_Deg(pos_to_end);
		chain->chain[i].angle += a_ptm - a_pte;
		dvec = MT_V2FromAngle_Deg(chain->chain[i].angle, chain->chain[i].length);

		endPoint.x -= chain->chain[i].vec.x - dvec.x;
		endPoint.y -= chain->chain[i].vec.y - dvec.y;
		dvec.x += position.x;
		dvec.y += position.y;
		i--;
	}

	return 	0;
}

void CalcIK(IK_Chain *chain, MT_Vector2 mouse)
{
	int i;
	int iter;
	double angle;

	MT_Vector2 endPoint;

	i = 0;
	iter = 0;
	endPoint = chain->start;
	while (i < chain->len)
	{
		chain->chain[i].vec = MT_V2FromAngle_Deg(chain->chain[i].angle, chain->chain[i].length);
		
		endPoint.x += chain->chain[i].vec.x;
		endPoint.y += chain->chain[i].vec.y;
		i++;
	}

	// while (iter < MAX_ITER) // Somehow iterating this breaks everything so I'll leave it like this for now...
	// {
		if (CalcAngle(chain, mouse, endPoint) == TRUE)
			return ;
	// 	iter++;
	// }
}

void DrawIk(IK_Chain *chain, SDLX_Display *display, MT_Vector2 mouse)
{
	MT_Vector2 vec;
	MT_Vector2 start;
	int i;

	i = 0;
	start = chain->start;
	FillCircle(display->renderer, (Circle){start.x , start.y, 7});
	FillCircle(display->renderer, (Circle){mouse.x, mouse.y, 5});
	while(i < chain->len)
	{
		vec = MT_V2FromAngle_Deg(chain->chain[i].angle, chain->chain[i].length);
		
		FillCircle(display->renderer, (Circle){start.x, start.y, 5});
		FillCircle(display->renderer, (Circle){start.x + vec.x, start.y + vec.y, 5});
		SDL_SetRenderDrawColor(display->renderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(display->renderer,
							start.x, start.y, start.x + vec.x, start.y + vec.y);
		start.x += vec.x;
		start.y += vec.y;
		i++;
	}
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}

