/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:35:39 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/15 09:35:35 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fractol.h>

int			fra_show_hud(const t_fra *fra)
{
	char	buffer[80];
	t_co	co;
	t_cooi	cooi;

	co = VCOTOI(255, 255, 255, 0);
	cooi = ACOOTOI(WIN_X - 120, WIN_Y - 15 * 8, 0);
	ft_sprintf(buffer, "%13s %s", "Movements:", "WASD");
	fra_put_string(*fra, ICOOADDY(cooi, 0), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Zoom:", "Scroll");
	fra_put_string(*fra, ICOOADDY(cooi, 15), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Positions:", "OP");
	fra_put_string(*fra, ICOOADDY(cooi, 30), co, buffer);
	ft_sprintf(buffer, "%13s %s", "This frame:", "I");
	fra_put_string(*fra, ICOOADDY(cooi, 45), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Num-loop coef:", "-+");
	fra_put_string(*fra, ICOOADDY(cooi, 60), co, buffer);
	ft_sprintf(buffer, "        (%d loops)", fra->max_loop);
	fra_put_string(*fra, ICOOADDY(cooi, 75), co, buffer);
	ft_sprintf(buffer, "%13s %s", "Color/Fractal:", "CV");
	fra_put_string(*fra, ICOOADDY(cooi, 90), co, buffer);
	return (0);
}

int			fra_set_cuspos1(t_fra *fra)
{
	fra->coo.x = STARTCAMX1;
	fra->coo.y = STARTCAMY1;
	fra->zoom = STARTZOOM1;
	fra->scdt.y = -1. / STARTZOOM1;
	fra->scdt.x = +1. / STARTZOOM1;
	fra_apply_zoom(fra, 1);
	return (0);
}

static int	readinput(int ac, char *av[])
{
	if (ac < 2 || av[1][0] == '\0' || av[1][1] != '\0')
		(void)ac;
	else if (*av[1] == 'J')
		return (1);
	else if (*av[1] == 'M')
		return (2);
	else if (*av[1] == 'S')
		return (3);
	ft_putendl("Invalid Arguments, Use:\n\t./fractol J/M/S");
	return (-1);
}

int			main(int ac, char *av[])
{
	t_fra	fra;
	F_T		sierp_deltas[MAX_SIERP_LOOPS];
	int		input;

	input = readinput(ac, av);
	if (input < 1)
		return (0);
	ft_bzero(&fra, sizeof(t_fra));
	fra.sierp_deltas = (F_T*)&sierp_deltas;
	fra_init_env(&fra, input);
	if (fra_init_window(&fra))
		return (1);
	fra_pause(&fra);
	(void)ac;
	(void)av;
	return (0);
}
