/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 18:24:38 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/30 18:40:26 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cmd_is_builtin(char **cmd_arg)
{
	int	i;

	i = 0;
	while (i < NB_BUILTINS)
	{
		if (!ft_strcmp(cmd_arg[0], g_builtins[i].builtin_name))
			return (i);
		i++;
	}
	return (-1);
}
