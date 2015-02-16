/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:19:40 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/02/10 14:03:39 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	ft_which_ops(char *str, t_env *env)
{
	if (strchr(str, '|') != NULL)
		ft_pipe(ft_strsplit(str, '|'), env);
	else if (strstr(str, "<<") != NULL)
		ft_double_io(ft_strsplit_spe(str, "<<"), env);
	else if (strstr(str, ">>") != NULL)
		ft_double_oi(ft_strsplit_spe(str, ">>"), env);
	else if (strchr(str, '<') != NULL)
		ft_simple_io(ft_strsplit(str, '<'), env);
	else if (strchr(str, '>') != NULL)
		ft_simple_oi(ft_strsplit(str, '>'), env);
}

void	ft_multiple_cmd(char **str, t_env *e)
{
	int		i;

	i = 0;
	while (str[i])
		ft_control(ft_strsplit(str[i], ' '), str[i], e), i++;
}

void	ft_which_builtin(char **str, t_env *e)
{
	if (ft_strcmp(str[0], "cd") == 0)
		ft_cd(str, e);
	else if (ft_strcmp(str[0], "env") == 0)
		ft_env(e);
	else if (ft_strcmp(str[0], "setenv") == 0 &&
			str[3] == NULL && ft_setenv_modify(e, str) != 1)
		ft_setenv(&e, str);
	else if (ft_strcmp(str[0], "unsetenv") == 0)
	{
		if (str[1] == NULL)
			ft_putendl_fd(TOOFEWARGS, 2);
		else
			ft_unsetenv(e, str);
	}
	else if (ft_strcmp(str[0], "exit") == 0)
		ft_exit();
	else if (str[1] != NULL && str[2] != NULL && str[3] != NULL)
		ft_putendl_fd(TOOMANYARGS, 2);
}

void	ft_control(char **str, char *line, t_env *e)
{
	char	*cmd;

	if (ft_is_pipe_redir(line) == 1)
		ft_which_ops(line, e);
	else if ((cmd = ft_verify_access(str, e)) != NULL &&
			(ft_is_builtin(str)) != 1)
		ft_execute_program(cmd, str, e->envcpy);
	else if (ft_is_builtin(str) == 1)
		ft_which_builtin(str, e);
	else if (str[0][0] == '.' && str[0][1] == '/')
		ft_executebin(str, e->envcpy);
	else if (str[0][0] == '/' && str[0][1] != '\0')
		ft_execute_program(str[0], str, e->envcpy);
	else
		ft_putstr_fd(NOTFOUND, 2), ft_putendl_fd(line, 2);
}
