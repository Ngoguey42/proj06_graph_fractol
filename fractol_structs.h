/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 11:01:12 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/25 11:01:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_STRUCTS_H
# define FRACTOL_STRUCTS_H

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
**		sierp_deltas:	float table of precalculated values for sierpinski.
**		theme:		current theme.
**		themes:		themes functions.
*/
typedef struct	s_fra
{
	void		*serv;
	void		*win1;
	t_img		s;
	int			ev[12];
	int			redraw;
	int			(*fra_func)(F_COO pix, const struct s_fra *fra);
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
	int			theme;
	t_co		(*themes[NUMTHEMES])(int v, int max);
}				t_fra;

/*
** 'struct s_frathread' Use for multi-threading.
*/

typedef struct	s_frathread
{
	const t_fra	*fra;
	int			part;
}				t_frathread;

#endif
