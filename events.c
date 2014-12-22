/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 09:17:49 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/22 06:55:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		fra_expose_hook(t_fra *fra)
{
	ft_printf("Expose Hook: %p\n", fra);
    fra_init_surface(*fra);
    fra_set_surface(*fra);
    fra_push_surface(*fra);
	fra_show_hud(*fra);
	return (0);
}

int		fra_keyup_hook(int keycode, t_fra *fra)
{
	if (keycode == FRAKEY_QUIT)
		fra_quit(*fra);
	else if (keycode == FRAKEY_P)
		fra_set_defpos1(fra);
	else if (keycode == FRAKEY_O)
		fra_set_defpos2(fra);
	else if (keycode == FRAKEY_W)
		fra->ev[0] = 0;
	else if (keycode == FRAKEY_S)
		fra->ev[1] = 0;
	else if (keycode == FRAKEY_A)
		fra->ev[4] = 0;
	else if (keycode == FRAKEY_D)
		fra->ev[5] = 0;
	return (0);
}

int		fra_keydo_hook(int keycode, t_fra *fra)
{
	if (keycode == FRAKEY_I)
		fra_show_hud(*fra);
	else if (keycode == FRAKEY_MIN)
	{
		fra->loop_coef -= fra->loop_coef < 0.15 ? 0. : 0.01;
		fra->redraw = 1;
		fra_show_hud(*fra);
	}
	else if (keycode == FRAKEY_EQU)
	{
		fra->loop_coef += fra->loop_coef > 5. ? 0. : 0.01;
		fra->redraw = 1;
		fra_show_hud(*fra);
	}
	else if (keycode == FRAKEY_W)
		fra->ev[0] = 1;
	else if (keycode == FRAKEY_S)
		fra->ev[1] = 1;
	else if (keycode == FRAKEY_A)
		fra->ev[4] = 1;
	else if (keycode == FRAKEY_D)
		fra->ev[5] = 1;
	return (0);
}

int		fra_butdo_hook(int keycode, int x, int y, t_fra *fra)
{
	if (keycode == 4)
		fra_apply_zoom(fra, ZOOMSPEEDBASE);
	else if (keycode == 5)
		fra_apply_zoom(fra, 1 / ZOOMSPEEDBASE);
/* 	fra->m_cooscr = ACOOTOI(x, y, 0); */
/* 	fra->ev[10] = 1; */
	return (0);
}

int		fra_motion_hook(int x, int y, t_fra *fra)
{
	fra->m_cooscr = ACOOTOI(x, y, 0);
	if (fra->type == 1)
	{
		fra_eval_screen_coords(fra, x, y);
/* 		fra->m_coo = ACOOTOL(fra->coo.x + fra->pxin.x * (F_T)x, */
/* 							fra->coo.y + fra->pxin.y * (F_T)y, 0); */
/* 		fra->redraw = 1; */
	}
/* 	qprintf("%d %d %p\n", x, y, fra); */
	return (0);
}

int     fra_parse_events(t_fra fra)
{
    int     i;

    i = 0;
    while (i < 6)
    {
        if (fra.ev[i])
            return (1);
        i++;
    }
    return (0);
}

int		fra_loop_hook(t_fra *fra)
{
    if (fra_parse_events(*fra))
    {
        fra->mvmt_clockev.cl = 6;
        ft_clock_updateone(&fra->mvmt_clockev);
    }
    ft_clock_loophook();
    if (fra->redraw)
    {
/* 		qprintf("loophook"); */
        fra->redraw = 0;
        fra_init_surface(*fra);
        fra_set_surface(*fra);
        fra_push_surface(*fra);
    }
    return (0);
}


