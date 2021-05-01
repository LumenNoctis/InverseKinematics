#include "IK.h"

double CalcAngle(MT_Vector2 tail, MT_Vector2 head, MT_Vector2 goal)
{
	SDLX_Display *display;
	MT_Vector2	line;
	MT_Vector2	lgoal;
	double		lineAngle;
	double		goalAngle;

	line.x = head.x - tail.x;
	line.y = head.y - tail.y;
	lgoal.x = goal.x - tail.x;
	lgoal.y = goal.y - tail.y;
	
	
	lineAngle = MT_V2Heading180_Deg(line);
	goalAngle = MT_V2Heading180_Deg(lgoal);

	return goalAngle - lineAngle;
}

void CalcIK(IK_Chain *chain, MT_Vector2 mouse)
{
	int i;
	double tlen;
	double tangle;
	double angle;
	MT_Vector2 vec;
	MT_Vector2 endPoint;


	tangle = 0;
	tlen = 0;
	endPoint = chain->start;
	i = 0;
	while (i < chain->len)
	{
		vec = MT_V2FromAngle_Deg(chain->chain[i].angle, chain->chain[i].length);
		// chain->chain[i].angle += angle;
		// SDL_Log("Angle %f\n", angle);
		chain->chain[i].vec = vec;
		endPoint.x += vec.x;
		endPoint.y += vec.y;
		i++;
	}
		SDL_Log("angle %f, len %f", chain->chain[0].angle, chain->chain[0].length);
	vec = endPoint;
	while (i >= 0)
	{
		vec = MT_V2Sub(vec, chain->chain[i].vec);
		if (MT_GetDistance2D(mouse, endPoint) <= MIN_DIST)
			return ;
		angle = CalcAngle(
		vec,
		endPoint,
		mouse);
		// chain->chain[i].angle = angle;
		endPoint = MT_V2Add(MT_V2Sub(endPoint, vec), MT_V2FromAngle_Deg(angle, 	chain->chain[i].length));
		FillCircle(SDLX_DisplayGet()->renderer, (Circle){endPoint.x, endPoint.y, 30});
		FillCircle(SDLX_DisplayGet()->renderer, (Circle){vec.x, vec.y, 30});
		i--;
	}

	// vec = MT_V2FromAngle_Deg(tangle, tlen);
}

void DrawIk(IK_Chain *chain, SDLX_Display *display, MT_Vector2 mouse, int state)
{
	MT_Vector2 vec;
	MT_Vector2 start;
	double angle;
	double tangle;
	double tlen;
	int i;

	i = 0;
	start = chain->start;
	if (state != 0)
		CalcIK(chain, mouse);
	while(i < chain->len)
	{
		vec = MT_V2FromAngle_Deg(chain->chain[i].angle, chain->chain[i].length);
		
		FillCircle(display->renderer, (Circle){start.x, start.y, 10});
		FillCircle(display->renderer, (Circle){mouse.x, mouse.y, 5});
		FillCircle(display->renderer, (Circle){start.x + vec.x, start.y + vec.y, 10});
		SDL_SetRenderDrawColor(display->renderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(display->renderer,
							start.x, start.y, start.x + vec.x, start.y + vec.y);
		// chain->chain[i].angle += angle;
		// SDL_Log("Angle %f\n", angle);
		start.x += vec.x;
		start.y += vec.y;
		i++;
	}
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}

