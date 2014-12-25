/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 12:13:24 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/25 11:06:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int				fra_sierpinski(F_COO pix, const t_fra *fra)
{
	int	i;
	F_T	tmp;

	i = 0;
	if (pix.x < 0 || pix.x > 3 || pix.y < 0 || pix.y > 3)
		return (-1);
	while (i <= fra->max_loop)
	{
		i++;
		tmp = F_MOD(pix.x / fra->sierp_deltas[i], 3);
		if (tmp > 1 && tmp < 2)
		{
			tmp = F_MOD(pix.y / fra->sierp_deltas[i], 3);
			if (tmp > 1 && tmp < 2)
				break ;
		}
	}
	return (i);
}

static F_COO	ft_cmult(F_COO c1, F_COO c2)
{
	F_T	tmp;

	tmp = c1.x;
	c1.x = c1.x * c2.x - c1.y * c2.y;
	c1.y = tmp * c2.y + c1.y * c2.x;
	return (c1);
}

int				fra_julia(F_COO pix, const t_fra *fra)
{
	int		i;

	i = 0;
	while (i < fra->max_loop)
	{
		i++;
		pix = ft_cmult(pix, pix);
		pix.x += fra->m_coo.x;
		pix.y += fra->m_coo.y;
		if (STOPCOND(pix.x) || STOPCOND(pix.y))
			break ;
	}
	return (i);
}

int				fra_mandelbrot(F_COO pix, const t_fra *fra)
{
	F_COO	zero;
	F_COO	tmp;
	int		i;

	ft_bzero(&zero, sizeof(F_COO));
	i = 0;
	while (i < fra->max_loop)
	{
		i++;
		tmp = zero;
		zero.y = 2 * tmp.x * tmp.y + pix.y;
		zero.x = tmp.x * tmp.x - tmp.y * tmp.y + pix.x;
		if (STOPCOND(zero.x) || STOPCOND(zero.y))
			break ;
	}
	return (i);
}
