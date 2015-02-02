/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 06:51:57 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/30 13:00:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdio.h>
# include <libft.h>
# include <ft_math.h>
# include <ft_clock.h>
#include <ft_debug.h> //debug

/*
** My SDL implementation's main purpose, was to be able to run fractol on
**	MinGW at home. That's why there's so few optimisation with it.
*/

# define USEMLX
# ifdef USEMLX
#  include <mlx.h>

#  define SERV fra.serv
#  define WIN1 fra.win1
#  define SERVP fra->serv
#  define WIN1P fra->win1

#  define FRAKEY_QUIT 65307
#  define FRAKEY_P 'p'
#  define FRAKEY_V 'v'
#  define FRAKEY_C 'c'
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

#  define WIN1 ((SDL_Surface*)fra.win1)
#  define WIN1P ((SDL_Surface*)fra->win1)

#  define FRAKEY_QUIT SDLK_ESCAPE
#  define FRAKEY_P SDLK_p
#  define FRAKEY_V SDLK_v
#  define FRAKEY_C SDLK_c
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
#  define F_MOD fmod
#  define F_FLOOR floor
#  define F_NEXT nextafter

# endif

# define NUMTHEMES 3
# define MAX_SIERP_LOOPS 500

# include <fractol_structs.h>

# define XYSPEEDBASE 0.03
# define ZOOMSPEEDBASE 1.005
# define DELTA_MVMT_CALLS (clock_t)(CLOCKS_PER_SEC / 48)

/*
** NUMTHREAD defined at compilation.
** SPEEDFACT is a quick fix to the clock() return being different
** on multi threading than on single threading.
*/

# ifndef NUMTHREAD
#  define NUMTHREAD 1
# endif

# if NUMTHREAD <= 1
#  define SPEEDFACT (F_T)DELTA_MVMT_CALLS / 1. * XYSPEEDBASE
# elif NUMTHREAD > 4
#  define SPEEDFACT (F_T)DELTA_MVMT_CALLS / 4. * XYSPEEDBASE
# else
#  define SPEEDFACT (F_T)DELTA_MVMT_CALLS / ((F_T)NUMTHREAD / 2.) * XYSPEEDBASE
# endif

/*
** Change WINY to change Frame size.
*/

# define WINY (500.)

# define WIN_Y (int)(WINY)
# define WIN_X (int)(WINY * 1.0)

# define DBG (0)

# define STARTCAMX2 -1.0
# define STARTCAMY2 1.0
# define STARTZOOM2 0.5

# define STARTCAMX3 +0.
# define STARTCAMY3 +3.
# define STARTZOOM3 (1./3.)

# define STARTCAMX1 -0xb.dacedfa66f81197p-4
# define STARTCAMY1 -0x9.34880019ca16063p-5
# define STARTZOOM1 0xe.00a24e21c9bc912p+47

# define NLOOPBIS(Z) ((Z > 10) ? F_LG(Z) / F_LG(10): 1.)
# define NLOOP (int)(70. * fra->loop_coef * NLOOPBIS(fra->zoom))

# define NLOOP2 (int)(140. * fra->loop_coef * NLOOPBIS(fra->zoom))

# define NLOOP3 (int)(fra->loop_coef * (F_FLOOR(F_LG(fra->zoom) / F_LG(3)) + 6))

# define STOPCOND(ARG) (ABS(ARG) > 100.)

/*
** Put pixels.
*/
int		fra_put_string(const t_fra *fra, t_cooi coo, t_co c, char *str);
int		fra_puts_pix(const t_fra *fra, t_cooi coo, t_co c);
int		fra_puts_fpix(const t_fra *fra, t_cood coof, t_co c);
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
int		fra_set_surface(t_fra *fra);
int		fra_push_surface(const t_fra *fra);

int		fra_draw_screen(const t_fra *fra);

int		fra_draw_scpart(const t_fra *fra, int part);
int		fra_draw_scpart_precisionloss(const t_fra *fra, int part);

int		fra_draw_row1(const t_fra *fra, F_COO pix, int sta, int end);
int		fra_draw_row2(const t_fra *fra, F_COO pix, int sta, int end);
int		fra_draw_row1_preci(const t_fra *fra, F_COO pix, int sta, int end);

int		fra_julia(F_COO pix, const t_fra *fra);
int		fra_mandelbrot(F_COO pix, const t_fra *fra);
int		fra_sierpinski(F_COO pix, const t_fra *fra);
int		fra_douady(F_COO pix, const t_fra *fra);
int		fra_tardis(F_COO pix, const t_fra *fra);
int		fra_toad(F_COO pix, const t_fra *fra);
int		fra_bretzel(F_COO pix, const t_fra *fra);
int		fra_test(F_COO pix, const t_fra *fra);

/*
** Env Modification.
*/
void	fra_init_env(t_fra *fra, int type);
void	fra_init_pertype(t_fra *fra, int type);
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
int		fra_motion_hook(int x, int y, t_fra *fra);

/*
** Misc.
*/
int		fra_show_hud(const t_fra *fra);
F_T		fra_get_n_nextval(F_T val, int n);
t_co	fra_theme_0(int c, int max);
t_co	fra_theme_1(int c, int max);
t_co	fra_theme_2(int c, int max);
F_COO	ft_cadd(F_COO c1, F_COO c2);
F_COO	ft_cmult(const F_COO *c1, const F_COO *c2);
F_COO	ft_cdiv(F_COO c1, F_COO c2);
F_COO	ft_csub(F_COO c1, F_COO c2);

#endif
