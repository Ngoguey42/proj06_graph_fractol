/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:35:39 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/15 16:04:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>

int	fra_set_defpos(t_fra *fra)
{
	fra->coo.x = STARTCAMX;
	fra->coo.y = STARTCAMY;
	fra->zoom = STARTZOOM;
	fra_apply_zoom(fra, 1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_fra	fra;

	#define PRINTCOORD(STRU) qprintf("%s: %.1f %.1f %.1f\n", #STRU, (double)STRU.x, (double)STRU.y, (double)STRU.z)

	(void)ac;
	(void)av;

	ft_bzero(&fra, sizeof(t_fra));
	fra.type = 2;
	// exit(0);
	if (fra_init_window(&fra))
		return (1);
	fra_set_defpos(&fra);
    fra.mvmt_clockev = (t_clockev){&fra_move_void, &fra,
								   CLOCKS_PER_SEC / 48, 0, 0, 0x11};
	fra_pause(&fra);
	return (0);
}
