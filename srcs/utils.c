#include "IK.h"

int AddJoint(IK_Chain *chain, double angle, double length)
{
	if (chain->len >= MAX_JOINTS)
		return 0;
	chain->chain[chain->len].angle = angle;
	chain->chain[chain->len].length = length;
	chain->len++;
	return 1;
}

int IK_Input(IK_Chain *chain, MT_Vector2 *mouse)
{
	SDL_Event event;
	static int state;
	static MT_Vector2 pos = {250.0, 250.0};
	int x;
	int y;
	Uint8 const	*kb;

	kb = SDL_GetKeyboardState(NULL);
	SDL_GetMouseState(&x, &y);
	mouse->x = x;
	mouse->y = y;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		if (event.type == SDL_KEYDOWN &&
			event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			state ^= 1;
			chain->len *= state;
			pos = (MT_Vector2){250.0, 250.0};
		}
		if (event.type == SDL_MOUSEBUTTONDOWN && state == 0)
		{
			chain->chain[chain->len].length = MT_V2Mag(MT_V2Sub(*mouse, pos));
			chain->chain[chain->len].angle = MT_V2Heading180_Deg(MT_V2Sub(*mouse, pos));
			pos = *mouse;
			chain->len++;
		}
	}
	return state;
}

void DrawCircle(SDL_Renderer *ren, Circle circle)
{
	int i;
	double x;
	double y;
	double val;
	double valx;
	double valy;

	i= 0;
	x = 0;
	valx = 0;
	y = circle.radius;
	val = 1 - circle.radius;
	valy = -2 * circle.radius;

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawPoint(ren, circle.x + circle.radius, circle.y);
	SDL_RenderDrawPoint(ren, circle.x - circle.radius, circle.y);
	SDL_RenderDrawPoint(ren, circle.x, circle.y + circle.radius);
	SDL_RenderDrawPoint(ren, circle.x, circle.y - circle.radius);

	while(x < y)
	{
		if(val > 0)
		{
			y--;
			valy += 2;
			val += valy;
		}
		x++;
        valx += 2;
        val += valx + 1;
		SDL_RenderDrawPoint(ren, circle.x + x, circle.y + y);
		SDL_RenderDrawPoint(ren, circle.x - x, circle.y + y);
		SDL_RenderDrawPoint(ren, circle.x + x, circle.y - y);
		SDL_RenderDrawPoint(ren, circle.x - x, circle.y - y);
		SDL_RenderDrawPoint(ren, circle.x - y, circle.y - x);
		SDL_RenderDrawPoint(ren, circle.x + y, circle.y - x);
		SDL_RenderDrawPoint(ren, circle.x - y, circle.y + x);
		SDL_RenderDrawPoint(ren, circle.x + y, circle.y + x);
		i += 8;
	}
	// printf("Points %d circumfrence %d",i,(int)( 2 * M_PI * circle.radius ));
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}

void FillCircle(SDL_Renderer *ren, Circle circle)
{
	double x;
	double y;
	double val;
	double valx;
	double valy;

	x = 0;
	valx = 0;
	y = circle.radius;
	val = 1 - circle.radius;
	valy = -2 * circle.radius;

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawLine(ren,
						circle.x + circle.radius, circle.y,
						circle.x - circle.radius, circle.y);
	SDL_RenderDrawLine(ren,
						circle.x, circle.y + circle.radius,
						circle.x, circle.y - circle.radius);
	while(x < y)
	{
		if(val > 0)
		{
			y--;
			valy += 2;
			val += valy;
		}
		x++;
        valx += 2;
        val += valx + 1;
		SDL_RenderDrawLine(ren,
							circle.x + x, circle.y + y,
							circle.x - x, circle.y + y);
		SDL_RenderDrawLine(ren,
							circle.x + x, circle.y - y,
							circle.x - x, circle.y - y);
		SDL_RenderDrawLine(ren,
							circle.x - y, circle.y - x,
							circle.x + y, circle.y - x);
		SDL_RenderDrawLine(ren,
							circle.x - y, circle.y + x,
							circle.x + y, circle.y + x);
	}
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}
