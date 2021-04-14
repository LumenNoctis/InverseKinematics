#include "../include/IK.h"


IK_Chain *InitIK()
{
	IK_Chain		*chain;

	SDLX_Start("Inverse Kinematics",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WIN_H, WIN_W, SDL_WINDOW_SHOWN);

	chain = calloc(1, sizeof(*chain));
	chain->start.x = WIN_W / 2;
	chain->start.y = WIN_H / 2;
	chain->len = 1;
	chain->chain[0].length = 42;
	chain->chain->angle = MT_ToRad(42);
}

int main(int argc, char **argv)
{
	SDLX_Display	*display;
 	IK_Chain		*chain;

	display = SDLX_DisplayGet();
	chain = InitIK();
	while (1)
	{
		IK_Input(chain);
		DrawIk(chain, display);
		SDL_RenderPresent(display->renderer);
	}
}
