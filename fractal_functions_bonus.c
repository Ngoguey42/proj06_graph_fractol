/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_functions_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 08:19:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/30 09:14:59 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int				fra_tardis(F_COO pix, const t_fra *fra)
{
	int		i;
	F_COO	tmp;
	F_COO	tmp2;

	i = 0;
	while (i < fra->max_loop)
	{
		i++;
		tmp = pix;
		pix = ft_cmult(&pix, &pix);
		tmp2 = (F_COO){0.56667, -0.5, 0.};
		tmp = ft_cmult(&tmp, &tmp2);
		pix = ft_cadd(tmp, pix);
		if (STOPCOND(pix.x) || STOPCOND(pix.y))
			break ;
	}
	return (i);
}

int				fra_douady(F_COO pix, const t_fra *fra)
{
	int		i;

	i = 0;
	while (i < fra->max_loop)
	{
		i++;
		pix = ft_cmult(&pix, &pix);
		pix.x += -0.123;
		pix.y += 0.745;
		if (STOPCOND(pix.x) || STOPCOND(pix.y))
			break ;
	}
	return (i);
}

int				fra_toad(F_COO pix, const t_fra *fra)
{
	int		i;

	i = 0;
	while (i < fra->max_loop)
	{
		i++;
		pix = ft_cmult(&pix, &pix);
		pix.y = cosl(pix.y) - sinl(pix.x);
		if (STOPCOND(pix.x) || STOPCOND(pix.y))
			break ;
	}
	return (i);
}

int				fra_bretzel(F_COO pix, const t_fra *fra)
{
	int		i;

	i = 0;
	while (i < fra->max_loop)
	{
		i++;
		pix.y = -sinl(pix.y) + cosl(pix.x);
		pix = ft_cmult(&pix, &pix);
		if (STOPCOND(pix.x) || STOPCOND(pix.y))
			break ;
	}
	return (i);
}

int				fra_test(F_COO pix, const t_fra *fra)
{
	int		i;

	i = 0;
	while (i < fra->max_loop)
	{
		i++;
		pix = ft_cadd(pix, pix);
		if (STOPCOND(pix.x) || STOPCOND(pix.y))
			break ;
	}
	return (i);
}
