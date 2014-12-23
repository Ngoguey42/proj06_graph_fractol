/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 06:51:57 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 12:53:25 by ngoguey          ###   ########.fr       */
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
#  define F_MOD fmodl
#  define F_FLOOR floorl
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
# define WINY (100. * 5.)

# define WIN_Y (int)(WINY)
# define WIN_X (int)(WINY * 1.0)

# define DBG (0)

# define XYSPEEDBASE 0.005
# define ZOOMSPEEDBASE 1.005

# define STARTCAMX2 -1.0
# define STARTCAMY2 1.0
# define STARTZOOM2 0.5

# define STARTCAMX3 +0.
# define STARTCAMY3 +3.
# define STARTZOOM3 (1./3.)

# define STARTCAMX1 -0xb.dacedfa66f81197p-4
# define STARTCAMY1 -0x9.34880019ca16063p-5
# define STARTZOOM1 0xe.00a24e21c9bc912p+47

/* x:- y: z: */

/* # define F_T double */
/* # define F_COO t_cood */

/* # define F_T float */
/* # define F_COO t_coof */
/* # define F_LG log2 */

#define DELTA_MVMT_CALLS (clock_t)(CLOCKS_PER_SEC / 48)
#define MAX_SIERP_LOOPS 10337

#define NLOOP (int)(70. * fra->loop_coef * ((fra->zoom > 10) ? F_LG(fra->zoom) / F_LG(10): 1.))

#define NLOOP3 (int)(fra->loop_coef * (F_FLOOR(F_LG(fra->zoom) / F_LG(3)) + 7))

#define STOPCOND(ARG) (ARG > 100.)

/*
** 'struct s_fra':
**		serv:		mlx X11 serv.
**		win1:		mlx & sdl window pointer.
**		s:			screen img struct. (see libft's ft_math.h)
**		ev:			events states for mouse/keyboard key press.
**		redraw:		redraw event.
**		mvmt_clockev:	Movements clockevent for my ft_clock lib.
**		coo:		top left point's coordinates.
**		zoom:		zoom's value. @zoom==1 == no zoom;
**		scdt:		screen delta. @zoom==1 == .x==2 .y==2
**		pxin:		pixel increment @zoom==1 == .x==2/WIN_X .y==2/WIN_Y
**		loop_coef:	loop coef applied on every fractals, to change precision.
**		max_loop:	number of loops.
**		precisionloss:	float critical precision loss status.
**		m_cooscr:	mouse screen coords inside the screen, as integer.
**		m_coo:		mouse plane coords, for zoom and Julia.
**		type:		fractal displayed
*/
typedef struct	s_fra
{
	void		*serv;
	void		*win1;
	t_img		s;
	int			ev[12];
	int			redraw;
	int			(*fra_func)(F_COO pix, const struct s_fra* fra);
	t_clockev	mvmt_clockev;
	F_COO		coo;
	F_T			zoom;
	F_COO		scdt;
	F_COO		pxin;
	F_T			loop_coef;
	int			max_loop;
	int			precisionloss;
	t_cooi		m_cooscr;
	F_COO		m_coo;
	int			type;
	F_T			*sierp_deltas;
}				t_fra;

typedef struct s_frathread
{
	const t_fra	*fra;
	int			part;
}				t_frathread;


/* int		fra_put_pix(t_fra fra, t_cooi coo, t_co c); */
/* int		fra_put_fpix(t_fra fra, t_cood coof, t_co c); */


/*
** Put pixels.
*/
int		fra_put_string(t_fra fra, t_cooi coo, t_co c, char *str);
int		fra_puts_pix(t_fra fra, t_cooi coo, t_co c);
int		fra_puts_fpix(t_fra fra, t_cood coof, t_co c);
int		fra_puts_dst(const t_img *s, int dst, t_co c);

/*
** Graph libs initialisations.
*/
int		fra_init_window(t_fra *fra);
void	fra_pause(t_fra *fra);
int		fra_quit(t_fra fra);

/*
** Drawing Functions.
*/
int		fra_init_surface(const t_fra *fra);
int 	fra_set_surface(t_fra *fra);
int		fra_push_surface(const t_fra *fra);

int		fra_draw_screen(const t_fra *fra);

int		fra_draw_scpart(const t_fra *fra, int part);
int		fra_draw_scpart_precisionloss(const t_fra *fra, int part);

int		fra_draw_row1(const t_fra *fra, F_COO pix, int sta, int end);
int		fra_draw_row2(const t_fra *fra, F_COO pix, int sta, int end);

int     fra_julia(F_COO pix, const t_fra *fra);
int     fra_mandelbrot(F_COO pix, const t_fra *fra);
int     fra_sierpinski(F_COO pix, const t_fra *fra);

/*
** Env Modification.
*/
void	fra_init_env(t_fra *fra, int type);
int		fra_set_defpos(t_fra *fra);
int		fra_set_cuspos1(t_fra *fra);
int		fra_move_void(void *fra, clock_t el);
int		fra_apply_zoom(t_fra *fra, F_T delta);
int		fra_eval_screen_coords(t_fra *fra, int x, int y);

/*
** Events.
*/
int		fra_loop_hook(t_fra *fra);
int		fra_expose_hook(t_fra *fra);
int		fra_keydo_hook(int keycode, t_fra *fra);
int		fra_keyup_hook(int keycode, t_fra *fra);
int		fra_butdo_hook(int keycode, int x, int y, t_fra *fra);
int     fra_motion_hook(int x, int y, t_fra *fra);
/* int		fra_mouse_hook(int button,int x,int y,t_fra *fra); */

/*
** Misc.
*/
int		fra_show_hud(const t_fra *fra);
/* int		fra_read_input(int ac, char *av[1], t_fra reffra, t_fra **fra_t[1]); */



#endif
