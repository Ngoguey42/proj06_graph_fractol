#include <fractol.h>

void	fra_pause(t_fra *fra)
{
	int			cont = 1;
	SDL_Event	event;
 
	while (cont)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			(void)fra_butdo_hook(event.button.button, event.button.x, event.button.y, fra);
		else if (event.type == SDL_MOUSEMOTION)
			(void)fra_motion_hook(event.motion.x, event.motion.y, fra);
		else if (event.type == SDL_KEYUP)
			(void)fra_keyup_hook(event.key.keysym.sym, fra);
		else if (event.type == SDL_KEYDOWN)
			(void)fra_keydo_hook(event.key.keysym.sym, fra);
		else if (event.type == SDL_VIDEOEXPOSE)
			(void)fra_expose_hook(fra);
		else if (event.type == SDL_QUIT)
			cont = 0;
		else
			fra_loop_hook(fra);
	}
}