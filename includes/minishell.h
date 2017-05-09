/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 13:42:13 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/09 14:17:33 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/param.h>
# include <signal.h>

# define NB_BUILTINS 5
# define INEXISTENT 1
# define MULTIPLE_ARGS 2
# define PERMISSION 3
# define NOT_DIRECTORY 4
# define COMMAND_NOT_FOUND 127
# define PERMISSION_DENIED 126

typedef struct		s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}					t_env;

typedef struct		s_shell
{
	t_env			*env;
	t_env			*mod_env;
	char			**envir;
	char			**cmd;
	char			**paths;
	int				exit_status;
	int				status;
	char			*shell_name;
	pid_t			ret;
}					t_shell;

typedef struct		s_builtins
{
	char			*builtin_name;
	int				(*builtins)(t_env **, char **);
}					t_builtins;

int					ft_cd(t_env **env, char **args);
int					ft_echo(t_env **env, char **args);
int					ft_env(t_env **env, char **args);
int					ft_exit(t_env *env, char **args);
int					ft_exit_error(char **args);
int					ft_setenv(t_env **env, char **args);
int					ft_unsetenv(t_env **env, char **args);
void				push_back_env(t_env **env, char *env_var);
void				set_var(t_env **env, char *var);
void				clear_env(t_env **env);
void				free_env(t_env **env);
int					display_env(t_env *env);
void				ft_perror(char *error);
void				ft_error_msg(char *error, char *cmd);
t_shell				*init_minishell(char **environ);
t_env				*create_node(char *env_var);
t_env				*dup_env(char **environ);
t_env				*ft_getenv(t_env *env, char *name);
t_env				*modified_env(t_env *env);
int					size_env(t_env *env);
int					check_access(char *cmd, char **cmd_arg, char **envir);
int					cmd_is_builtin(char **cmd_arg);
char				**env_to_tab(t_env *env);
char				**ft_get_cmd(void);
void				update_wd(t_env **env, char **wd);
char				*set_home_path(t_env *env, char *path);
char				*set_oldpwd_path(t_env *env, char *path);
void				minishell_prompt(void);

static t_builtins g_builtins[] = {
	{ "cd", ft_cd },
	{ "echo", ft_echo },
	{ "env", ft_env},
	{ "setenv", ft_setenv },
	{ "unsetenv", ft_unsetenv},
};
#endif
