/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 09:17:49 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/12 15:21:21 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		fra_expose_hook(t_fra *fra)
{
	ft_printf("Expose Hook: %p\n", fra);
    fra_init_surface(*fra);
    fra_set_surface(*fra);
    fra_push_surface(*fra);
	return (0);
}

int		fra_keyup_hook(int keycode, t_fra *fra)
{
	int	t;

	t = 0;
	if (keycode == KEYQUI)
		fra_quit(*fra);
	if (keycode == 'p')
	{
/* 	fra_init_surface(*fra); */
		fra_set_defpos(fra);
	}
	else if (keycode == 'w' && (t = 1))
		fra->ev[0] = 0;
	else if (keycode == 's' && (t = 1))
		fra->ev[1] = 0;
/* 	else if (keycode == 'q' && (t = 1)) */
/* 		fra->ev[2] = 0; */
/* 	else if (keycode == 'e' && (t = 1)) */
/* 		fra->ev[3] = 0; */
	else if (keycode == 'a' && (t = 1))
		fra->ev[4] = 0;
	else if (keycode == 'd' && (t = 1))
		fra->ev[5] = 0;
/* 	else if (keycode == ' ' && (t = 1)) */
/* 		fra->ev[6] = 0; */
/* 	else if (keycode == 'c' && (t = 1)) */
/* 		fra->ev[7] = 0; */
/* 	else if (keycode == KEYTUP && (t = 1)) */
/* 		fra->ev[8] = 0; */
/* 	else if (keycode == KEYTDO && (t = 1)) */
/* 		fra->ev[9] = 0; */
	return (0);
}

int		fra_keydo_hook(int keycode, t_fra *fra)
{
	int	t;

/* 	qprintf("received %p\n", fra); */
	t = 0;
	if (keycode == 'i')
		fra_debug(*fra);
	else if (keycode == 'w' && (t = 1))
		fra->ev[0] = 1;
	else if (keycode == 's' && (t = 1))
		fra->ev[1] = 1;
/* 	else if (keycode == 'q' && (t = 1)) */
/* 		fra->ev[2] = 1; */
/* 	else if (keycode == 'e' && (t = 1)) */
/* 		fra->ev[3] = 1; */
	else if (keycode == 'a' && (t = 1))
		fra->ev[4] = 1;
	else if (keycode == 'd' && (t = 1))
		fra->ev[5] = 1;
/* 	else if (keycode == ' ' && (t = 1)) */
/* 		fra->ev[6] = 1; */
/* 	else if (keycode == 'c' && (t = 1)) */
/* 		fra->ev[7] = 1; */
/* 	else if (keycode == KEYTUP && (t = 1)) */
/* 		fra->ev[8] = 1; */
/* 	else if (keycode == KEYTDO && (t = 1)) */
/* 		fra->ev[9] = 1; */
	return (0);
}

int		fra_butdo_hook(int keycode, int x, int y, t_fra *fra)
{
/* 	qprintf("received %p\n", fra); */
/* 	qprintf("lol"); */
/* 	if (keycode == 4) */
/* 		fra->ev[2] = 1; */
/* 	else if (keycode == 5) */
/* 		fra->ev[3] = 1; */
/* 	(void)x; */
/* 	(void)y; */

	if (keycode == 4)
		fra_apply_zoom(fra, ZOOMSPEEDBASE);
	else if (keycode == 5)
		fra_apply_zoom(fra, 1 / ZOOMSPEEDBASE);
	fra->m_cooscr = ACOOTOI(x, y, 0);
	fra->ev[10] = 1;
/* 	qprintf("butdo(%d)\n", keycode); */
	(void)fra;
	(void)keycode;
	return (0);
}

int		fra_butup_hook(int keycode, int x, int y, t_fra *fra)
{
/* 	qprintf("lol"); */
	if (keycode == 4)
		fra->ev[2] = 0;
	else if (keycode == 5)
		fra->ev[3] = 0;
	(void)x;
	(void)y;
	return (0);
}

int     fra_parse_events(t_fra fra)
{
    int     i;

    i = 0;
    while (i < 6)
    {
        if (fra.ev[i])
            return (1);
        i++;
    }
    return (0);
}

int		fra_loop_hook(t_fra *fra)
{
    if (fra_parse_events(*fra))
    {
        fra->mvmt_clockev.cl = 6;
        ft_clock_updateone(&fra->mvmt_clockev);
    }
    ft_clock_loophook();
    if (fra->redraw)
    {
        fra->redraw = 0;
        fra_init_surface(*fra);
        fra_set_surface(*fra);
        fra_push_surface(*fra);
    }
    return (0);
/* 	int	t; */

/* 	t = 0; */
/* 	t += fra_move(fra); */
/* 	t += fra->ev[10]; */
/* 	if (t == 0) */
/* 		return (0); */
/* 	fra->ev[10] = 0; */
/* 	fra_init_surface(*fra); */
/* 	fra_set_surface(*fra); */
/* 	fra_push_surface(*fra); */
/* 	return (0); */
}


