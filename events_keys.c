/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/22 08:51:12 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 12:53:47 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		fra_keyup_hook(int keycode, t_fra *fra)
{
	if (keycode == FRAKEY_QUIT)
		fra_quit(*fra);
	else if (keycode == FRAKEY_O)
		fra_set_defpos(fra);
	else if (keycode == FRAKEY_P)
		fra_set_cuspos1(fra);
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
		fra_show_hud(fra);
	else if (keycode == FRAKEY_MIN)
	{
		fra->loop_coef -= fra->loop_coef < 0.15 ? 0. : 0.01;
		fra->redraw = 1;
		fra_show_hud(fra);
	}
	else if (keycode == FRAKEY_EQU)
	{
		fra->loop_coef += fra->loop_coef > 5. ? 0. : 0.01;
		fra->redraw = 1;
		fra_show_hud(fra);
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
	(void)x;
	(void)y;
	return (0);
}

int		fra_motion_hook(int x, int y, t_fra *fra)
{
	fra->m_cooscr = ACOOTOI(x, y, 0);
	return (0);
}
