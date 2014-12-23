/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen_sync.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 11:55:19 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 11:58:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int				fra_draw_screen(const t_fra *fra)
{
	if (fra->precisionloss)
		return (fra_draw_scpart_precisionloss(fra, 1));
	return (fra_scpart(fra, 1));
}
