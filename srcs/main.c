#include "IK.h"


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
	chain->len = 0;
// 	chain->chain[0].length = 100;
// 	chain->chain->angle = 42;
}

int main(int argc, char **argv)
{
	SDLX_Display	*display;
	MT_Vector2		mouse;
 	IK_Chain		*chain;
	int				state;

	display = SDLX_DisplayGet();
	chain = InitIK();
	while (1)
	{
		state = IK_Input(chain, &mouse);
		DrawIk(chain, display, mouse, state);
		SDL_RenderPresent(display->renderer);
		SDLX_ResetWindow();
	}
}
