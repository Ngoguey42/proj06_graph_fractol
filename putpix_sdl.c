
#include <fractol.h>

int fra_put_string(t_fra fra, t_cooi coo, t_co c, char *str)
{
	// return (mlx_string_put(SERV, WIN1, coo.x, coo.y, c.i, str));
	(void)fra;
	(void)coo;
	(void)c;
	(void)str;
}

int fra_puts_pix(t_fra fra, t_cooi coo, t_co c)
{
    t_ui32	*pixmem32;

    pixmem32 = (t_ui32*)WIN1->pixels + coo.y * WIN1->pitch/4 + coo.x;
    *pixmem32 = SDL_MapRGB(WIN1->format, c.s.r, c.s.g, c.s.b);
	return (0);
}

int fra_puts_fpix(t_fra fra, t_cood coof, t_co c)
{
    return (fra_puts_pix(fra, DCOOTOI(coof), c));
}

int	fra_puts_dst(t_fra fra, int dst, t_co c)
{
	*(t_ui32*)((char*)WIN1->pixels + dst) =
		SDL_MapRGB(WIN1->format, c.s.r, c.s.g, c.s.b);
	return (0);
}
