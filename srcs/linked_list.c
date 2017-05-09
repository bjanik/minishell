/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:47:39 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/09 21:04:02 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			size_env(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

static void	copy_content(t_env *env, t_env *mod_env)
{
	if (!(mod_env->var_name = ft_strdup(env->var_name)))
		ft_perror("malloc failed");
	if (!(mod_env->var_value = ft_strdup(env->var_value)))
		ft_perror("malloc failed");
	mod_env->next = NULL;
}

t_env		*modified_env(t_env *env)
{
	t_env	*mod_env;
	t_env	*ptr;

	mod_env = NULL;
	while (env)
	{
		if (!mod_env)
		{
			if (!(mod_env = (t_env*)malloc(sizeof(t_env))))
				ft_perror("malloc failed");
			copy_content(env, mod_env);
			ptr = mod_env;
		}
		else
		{
			if (!(ptr->next = (t_env*)malloc(sizeof(t_env))))
				ft_perror("malloc failed");
			ptr = ptr->next;
			copy_content(env, ptr);
		}
		env = env->next;
	}
	return (mod_env);
}

t_env		*create_node(char *env_var)
{
	t_env	*env;
	char	**splitted_env_var;
	
	if (!env_var)
		return (NULL);
	splitted_env_var = ft_strsplit(env_var, '=');
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		ft_perror("malloc failed");
	if (!(env->var_name = ft_strdup(splitted_env_var[0])))
		ft_perror("malloc failed");
	if (splitted_env_var[1])
	{
		if (!(env->var_value = ft_strdup(splitted_env_var[1])))
			ft_perror("malloc failed");
	}
	else if (!(env->var_value = ft_strdup("")))
		ft_perror("malloc failed");
	env->next = NULL;
	ft_free_string_tab(&splitted_env_var);
	return (env);
}

void		push_back_env(t_env **env, char *env_var)
{
	t_env	*ptr;

	if (*env)
	{
		ptr = *env;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = create_node(env_var);
	}
	else
		*env = create_node(env_var);
}
