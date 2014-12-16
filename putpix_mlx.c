/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putsmallobj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 14:47:13 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/16 09:10:48 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int fra_put_string(t_fra fra, t_cooi coo, t_co c, char *str)
{
	return (mlx_string_put(SERV, WIN1, coo.x, coo.y, c.i, str));
}

int fra_puts_pix(t_fra fra, t_cooi coo, t_co c)
{
	const int dst	= fra.s.lsz * coo.y + coo.x * (fra.s.bpp / 8);
	int				i;

	i = -1;
	while (++i < (fra.s.bpp / 8))
	{
		fra.s.dat[dst + i] = (char)c.s.b;
		c.i >>= 8 ;
	}
	return (0);
}

int fra_puts_fpix(t_fra fra, t_cood coof, t_co c)
{
    return (fra_puts_pix(fra, DCOOTOI(coof), c));
}

int	fra_puts_dst(t_fra fra, int dst, t_co c)
{
	int				i;

	i = -1;
	while (++i < (fra.s.bpp / 8))
	{
		fra.s.dat[dst + i] = (char)c.s.b;
		c.i >>= 8 ;
	}
	fra.s.dat[dst] = c.i;
	return (0);
}
