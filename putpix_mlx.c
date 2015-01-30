/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpix_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/22 08:55:14 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/30 07:13:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int fra_put_string(const t_fra *fra, t_cooi coo, t_co c, char *str)
{
	return (mlx_string_put(SERVP, WIN1P, coo.x, coo.y, c.i, str));
}

int fra_puts_pix(const t_fra *fra, t_cooi coo, t_co c)
{
	const int	dst = fra->s.lsz * coo.y + coo.x * (fra->s.bpp / 8);
	int			i;

	i = -1;
	while (++i < (fra->s.bpp / 8))
	{
		fra->s.dat[dst + i] = (char)c.s.b;
		c.i >>= 8;
	}
	return (0);
}

int fra_puts_fpix(const t_fra *fra, t_cood coof, t_co c)
{
	return (fra_puts_pix(fra, DCOOTOI(coof), c));
}

int	fra_puts_dst(const t_img *s, int dst, t_co c)
{
	int				i;

	i = -1;
	while (++i < (s->bpp / 8))
	{
		s->dat[dst + i] = (char)c.s.b;
		c.i >>= 8;
	}
	return (0);
}
