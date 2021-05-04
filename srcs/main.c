#include "IK.h"


IK_Chain *InitIK()
{
	IK_Chain		*chain;

	SDLX_Start("Inverse Kinematics",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WIN_H, WIN_W, SDL_WINDOW_SHOWN);

	chain = calloc(1, sizeof(*chain));
	chain->len = 0;
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
		if (state != 0)
			CalcIK(chain, mouse);
		DrawIk(chain, display, mouse);
		SDL_RenderPresent(display->renderer);
		SDLX_ResetWindow();
	}
}
