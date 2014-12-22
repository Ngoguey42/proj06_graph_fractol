/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 06:51:57 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/22 06:54:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdio.h>
# include <libft.h>
# include <ft_math.h>
# include <ft_clock.h>
// # include <ft_error.h>

# define USEMLX
# ifdef USEMLX
#  include <mlx.h>
#  define SERV fra.serv
#  define WIN1 fra.win1
#  define SERVP fra->serv
#  define WIN1P fra->win1

#  define FRAKEY_QUIT 65307
#  define FRAKEY_P 'p'
#  define FRAKEY_O 'o'
#  define FRAKEY_W 'w'
#  define FRAKEY_S 's'
#  define FRAKEY_A 'a'
#  define FRAKEY_D 'd'
#  define FRAKEY_I 'i'
#  define FRAKEY_MIN '-'
#  define FRAKEY_EQU '='
#  define FRAKEY_SCROLLUP 4
#  define FRAKEY_SCROLLDOWN 5
#  define FRAKEY_UP 65362
#  define FRAKEY_DO 65364
#  define FRAKEY_SPACE ' '

#  define F_T long double
#  define F_COO t_cool
#  define F_LG log2l
#  define F_NEXT nextafterl

# else
#  include <SDL/SDL.h>
// #  include <float.h>
#  define WIN1 ((SDL_Surface*)fra.win1)
#  define WIN1P ((SDL_Surface*)fra->win1)

#  define FRAKEY_QUIT SDLK_ESCAPE
#  define FRAKEY_P SDLK_p
#  define FRAKEY_O SDLK_o
#  define FRAKEY_W SDLK_w
#  define FRAKEY_S SDLK_s
#  define FRAKEY_A SDLK_a
#  define FRAKEY_D SDLK_d
#  define FRAKEY_I SDLK_i
#  define FRAKEY_MIN SDLK_MINUS
#  define FRAKEY_EQU SDLK_EQUALS
#  define FRAKEY_SCROLLUP 4
#  define FRAKEY_SCROLLDOWN 5
#  define FRAKEY_UP SDLK_UP
#  define FRAKEY_DO SDLK_DOWN
#  define FRAKEY_SPACE SDLK_SPACE

#  define F_T long double
#  define F_COO t_cool
#  define F_LG log2
#  define F_NEXT nextafter

# endif

#define PEACE(A1, A2) A1 A2; (void)A2


# define NUMTHREAD 8

/* # define WINY (128. * 4.) */
// # define WINY 600.
# define WINY 100. * 5.

# define WIN_Y (int)(WINY)
# define WIN_X (int)(WINY * 1.0)

# define DBG (0)

# define XYSPEEDBASE 0.005
# define ZOOMSPEEDBASE 1.005

# define STARTCAMX2 -1.0
# define STARTCAMY2 1.0
# define STARTZOOM2 0.5

# define STARTCAMX1 -0xb.dacedfa66f81197p-4
# define STARTCAMY1 -0x9.34880019ca16063p-5
# define STARTZOOM1 0xe.00a24e21c9bc912p+47

#define _PD1(A) (A <fra.max_loop)
#define _PD2(A) VCOTOI((A * 7) % 256, 0, 0, 0)
#define _PD3 VCOTOI(0, 0, 0, 255)
#define PUTSDST(A, B) fra_puts_dst(fra, (B) * 4, _PD1(A) ? _PD2(A) : _PD3)

/* x:- y: z: */

/* # define F_T double */
/* # define F_COO t_cood */

/* # define F_T float */
/* # define F_COO t_coof */
/* # define F_LG log2 */



#define NLOOP (int)(70. * fra.loop_coef * ((fra.zoom > 10) ? F_LG(fra.zoom) / F_LG(10): 1.))
#define STOPCOND(ARG) (ARG > 100.)

/*
** 'struct s_fra':
**		serv:		mlx X11 serv.
**		win1:		mlx & sdl window pointer.
**		s:			screen img struct. (see libft's ft_math.h)
**		ev:			events states for mouse/keyboard key press.
**		coo:		top left point's coordinates.
**		zoom:		zoom's value. @zoom==1 == no zoom;
**		scdt:		screen delta. @zoom==1 == .x==2 .y==2
**		pxin:		pixel increment @zoom==1 == .x==2/WIN_X .y==2/WIN_Y
**		m_cooscr:	mouse screen coords inside the screen, as integer.
**		type:		fractal displayed
**		j:			Julia's datas.
*/
typedef struct	s_fra
{
	void		*serv;
	void		*win1;
	t_img		s;
	int			ev[12];
	t_clockev	mvmt_clockev;
	int			redraw;
	F_COO		coo;
	F_T			zoom;
	F_T			loop_coef;
	F_COO		scdt;
	F_COO		pxin;
	int			max_loop;
	int			precisionloss;
	t_cooi		m_cooscr;
	F_COO		m_coo;
	int			type;
	int			part;
}				t_fra;

int		fra_put_pix(t_fra fra, t_cooi coo, t_co c);
int		fra_put_fpix(t_fra fra, t_cood coof, t_co c);
int		fra_put_string(t_fra fra, t_cooi coo, t_co c, char *str);

int		fra_puts_pix(t_fra fra, t_cooi coo, t_co c);
int		fra_puts_fpix(t_fra fra, t_cood coof, t_co c);


int		fra_puts_dst(t_fra fra, int dst, t_co c);

void	fra_pause(t_fra *fra);

int     fra_draw_julia(t_fra fra);
int     fra_draw_mandelbrot(t_fra fra);

int		fra_init_window(t_fra *fra);
int		fra_init_surface(t_fra fra);
int 	fra_set_surface(t_fra fra);
int		fra_push_surface(t_fra fra);
int		fra_quit(t_fra fra);

int		fra_set_defpos1(t_fra *fra);
int		fra_set_defpos2(t_fra *fra);
int		fra_move(t_fra *fra);
int		fra_move_void(void *fra);
int		fra_apply_zoom(t_fra *fra, F_T delta);

int		fra_expose_hook(t_fra *fra);
int		fra_keydo_hook(int keycode, t_fra *fra);
int		fra_keyup_hook(int keycode, t_fra *fra);
int		fra_butdo_hook(int keycode, int x, int y, t_fra *fra);
/* int		fra_butup_hook(int keycode, int x, int y, t_fra *fra); */

int     fra_motion_hook(int x, int y, t_fra *fra);
int		fra_mouse_hook(int button,int x,int y,t_fra *fra);
int		fra_loop_hook(t_fra *fra);
int		fra_eval_screen_coords(t_fra *fra, int x, int y);

/* int		fra_read_input(int ac, char *av[1], t_fra reffra, t_fra **fra_t[1]); */

int		fra_show_hud(t_fra fra);

#endif
