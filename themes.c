/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 12:59:26 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 13:36:49 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_co		fra_theme_0(int v, int max)
{
	if (v == max)
		return (VCOTOI(0, 0, 0, 0));
	return (VCOTOI(v * 7 % 256, 0, 0, 0));
}

t_co		fra_theme_1(int v, int max)
{
	if (v == max)
		return (VCOTOI(0, 0, 0, 0));
	if (v < 0)
		return (VCOTOI(255, 255, 255, 0));
	return (VCOTOI(55 + v * 18 % 200, 0, 55 + v * 23 % 200, 0));
}
