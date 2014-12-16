/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 08:56:44 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/16 09:34:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdlib.h>

int     fra_read_input(int ac, char *av[1], t_fra reffra, t_fra **frat[1])
{
	int		i;
	int		toi;
	int		n;

	i = 0;
	n = -1;
	while (++i < ac)
	{
		toi = ft_atoi(av[i]);
		qprintf("%d\n", toi);
		if (toi >= 1 && toi <= 2)
		{
			if (ft_tabaddm((void***)frat, (void*)&reffra, sizeof(t_fra)))
				exit(0);
/* 			qprintf("%p \n", frat); */
/* 			qprintf("%p \n", *frat); */
/* 			qprintf("%p \n", (*frat)[); */
/* 			qprintf("%p \n", ); */
			(*frat)[++n]->type = toi;
			qprintf("new %p\n", (*frat)[n]);
			if (fra_init_window((*frat)[n]))
				return (1);
		}
	}
	if (n > -1)
		fra_pause((*frat)[n]);
	return (0);
}
