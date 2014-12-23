/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen_async.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 11:37:07 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/23 11:58:52 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <pthread.h>

static void		*threadsplit(void *threadpv)
{
	if (((t_frathread*)threadpv)->fra->precisionloss)
		fra_draw_scpart_precisionloss(((t_frathread*)threadpv)->fra,
									((t_frathread*)threadpv)->part);
	else
		fra_draw_scpart(((t_frathread*)threadpv)->fra,
						((t_frathread*)threadpv)->part);
	return (NULL);
}

int				fra_draw_screen(const t_fra *fra)
{
	pthread_t   tid[NUMTHREAD];
	t_frathread	threads[NUMTHREAD];
	int			i;

	i = 0;
	while (i < NUMTHREAD)
	{
		threads[i].fra = fra;
		threads[i].part = i + 1;
		pthread_create(&tid[i], NULL, threadsplit, &threads[i]);
		i++;
	}
	i = 0;
	while (i < NUMTHREAD)
		pthread_join(tid[i++], NULL);
	return (0);	
}
