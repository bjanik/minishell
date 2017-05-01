/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 18:26:17 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/01 19:40:27 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(char *cmd, char **cmd_arg, char **envir)
{
	if (!access(cmd, F_OK))
	{
		if (access(cmd, X_OK))
			return (1);
		else
			execve(cmd, cmd_arg, envir);
	}
	return (0);
}
