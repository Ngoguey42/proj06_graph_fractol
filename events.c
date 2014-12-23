/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 09:17:49 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 11:24:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int	fra_expose_hook(t_fra *fra)
{
	ft_printf("Expose Hook: %p\n", fra);
	fra_init_surface(fra);
	fra_set_surface(fra);
	fra_push_surface(fra);
	fra_show_hud(fra);
	return (0);
}

int	fra_parse_events(t_fra fra)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (fra.ev[i])
			return (1);
		i++;
	}
	return (0);
}

int	fra_loop_hook(t_fra *fra)
{
	if (fra_parse_events(*fra))
	{
		fra->mvmt_clockev.cl = 6;
		ft_clock_updateone(&fra->mvmt_clockev);
	}
	ft_clock_loophook();
	if (fra->redraw)
	{
		fra->redraw = 0;
		if (fra->type == 1)
			fra_eval_screen_coords(fra, fra->m_cooscr.x, fra->m_cooscr.y);
		fra_init_surface(fra);
		fra_set_surface(fra);
		fra_push_surface(fra);
	}
	return (0);
}
