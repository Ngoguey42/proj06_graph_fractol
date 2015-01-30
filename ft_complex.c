/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 08:12:46 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/30 09:11:11 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

F_COO	ft_cmult(const F_COO *c1, const F_COO *c2)
{
	return ((F_COO){c1->x * c2->x - c1->y * c2->y,
		c1->x * c2->y + c1->y * c2->x, 0});
}

F_COO	ft_cdiv(F_COO c1, F_COO c2)
{
	F_T tmp;

	tmp = c1.x;
	c1.x = c1.x / c2.x - c1.y / c2.y;
	c1.y = tmp / c2.y + c1.y / c2.x;
	return (c1);
}

F_COO	ft_cadd(F_COO c1, F_COO c2)
{
	return ((F_COO){c1.x + c2.x, c1.y + c1.y, 0.});
}

F_COO	ft_csub(F_COO c1, F_COO c2)
{
	return ((F_COO){c1.x - c2.x, c1.y - c1.y, 0.});
}
