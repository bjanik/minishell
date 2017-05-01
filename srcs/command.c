/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:34:27 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/01 19:43:39 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_cmd(void)
{
	char	*tmp;
	char	*line;
	char	**cmd;

	get_next_line(0, &line);
	tmp = line;
	line = ft_strtrim(tmp);
	ft_strdel(&tmp);
	cmd = ft_strtok(line, "\t ");
	ft_strdel(&line);
	return (cmd);
}
