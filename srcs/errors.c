/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 18:20:36 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/04 11:35:54 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *error)
{
	ft_putendl_fd(error, 2);
	exit(-1);
}

void	ft_error_msg(char *error, char *cmd)
{
	ft_putstr_fd(error, 2);
	ft_putendl_fd(cmd, 2);
}
