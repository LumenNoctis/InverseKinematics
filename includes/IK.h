#ifndef IK_H
# define IK_H

# include "MT/MT.h"
# include "MT/MT_vec2.h"
# include "SDLX/SDLX.h"

#define MAX_JOINTS 10
#define MIN_DIST 5
#define MAX_ITER 10
#define TRUE	1
#define FAlSE	0

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

int		IK_Input(IK_Chain *chain, MT_Vector2 *mouse);

void CalcIK(IK_Chain *chain, MT_Vector2 mouse);
void DrawIk(IK_Chain *chain, SDLX_Display *display, MT_Vector2 mouse);
void DrawLine(MT_Vector2 slope, double b);

int AddJoint(IK_Chain *chain, double angle, double length);

void FillCircle(SDL_Renderer *ren, Circle circle);
void DrawCircle(SDL_Renderer *ren, Circle circle);

#endif
