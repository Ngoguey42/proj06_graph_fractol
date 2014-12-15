/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 08:57:28 by ngoguey           #+#    #+#             */
/*   Updated: 2014/12/11 06:58:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	fra_pause(t_fra *fra)
{
	fra_init_surface(*fra);
	fra_set_surface(*fra);
	fra_push_surface(*fra);
	mlx_loop(SERVP);
}

