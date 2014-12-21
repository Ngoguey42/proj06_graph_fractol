
#include <fractol.h>

int	fra_init_window(t_fra *fra)
{
    SDL_Init(SDL_INIT_VIDEO);
    fra->win1 = (void*)SDL_SetVideoMode(WIN_X, WIN_Y, 32, SDL_HWSURFACE);
    if (WIN1P == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
		ft_dprintf(2, "Could not create new window : %s\n", SDL_GetError());
		return (1);
    }
	ft_dprintf(2, "New window created. %p\n", WIN1P);
    SDL_WM_SetCaption("Fractol", NULL);
	return (0);
}

int	fra_init_surface(t_fra fra)
{
	SDL_LockSurface(WIN1);
	return (0);
}

int fra_set_surface(t_fra fra)
{
	if (fra.type == 1)
		fra_draw_julia(fra);
	else if (fra.type == 2)
		fra_draw_mandelbrot(fra);
	return (0);
}

int	fra_push_surface(t_fra fra)
{
	SDL_UnlockSurface(WIN1);
	SDL_Flip(WIN1); 
	return (0);
}

int	fra_quit(t_fra fra)
{
    SDL_Quit();
	(void)fra;
	exit(EXIT_SUCCESS);
}