/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 10:44:55 by ngoguey           #+#    #+#             */
/*   Updated: 2015/01/30 10:22:51 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_envdel(char **env, const char *key)
{
	char	*line;
	size_t	envlen;

	if (env == NULL)
		return (1);
	line = ft_envget((const char**)env, key);
	if (line == NULL)
		return (1);
	envlen = 0;
	while (env[envlen] != NULL)
		envlen++;
	while (*env != line)
	{
		env++;
		envlen--;
	}
	ft_memmove(env, env + 1, envlen * sizeof(char*));
	return (0);
}
