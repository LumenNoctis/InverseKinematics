#ifndef IK_H
# define IK_H

# include "MT/MT.h"
# include "MT/MT_vec2.h"
# include "SDLX/SDLX.h"

#define MAX_JOINTS 10

typedef struct	Joint
{
	double		angle;
	double		length;
	MT_Vector2	vec;
}				IK_Joint;

typedef struct IK_Chain_t
{
	int				len;
	MT_Vector2		start;
	IK_Joint		chain[MAX_JOINTS];
}				IK_Chain;

typedef struct Circle
{
	double x;
	double y;
	double radius;
}				Circle;

void IK_Input(IK_Chain *chain);
void DrawIk(IK_Chain *chain, SDLX_Display *display);

int AddJoint(IK_Chain *chain, double angle, double length);

void FillCircle(SDL_Renderer *ren, Circle circle);
void DrawCircle(SDL_Renderer *ren, Circle circle);

#endif
