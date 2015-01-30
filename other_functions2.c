/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 17:35:02 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/01/30 17:40:33 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

char	*verify_access(char **str, t_env *e)
{
	char	*perms;
	char	*cool;
	char	**paths;
	int		i;

	i = 0;
	perms = ft_strnew(1);
	paths = ft_getpaths(ft_getenv(e->envcpy, "PATH"));
	while (paths[i] != NULL)
	{
		perms = ft_strjoin(ft_strjoin(perms, paths[i]), "/");
		perms = ft_strjoin(perms, str[0]);
		cool = perms, free(perms);
		if ((access(cool, R_OK)) == 0)
			return (cool);
		i++, ft_bzero(cool, 1);
	}
	return (NULL);
}

void	execute_program(char *ok, char **str, char **env)
{
	int		status;
	pid_t	pid;

	pid = fork();
	ok = ok;
	if (pid == 0)
	{
		if (execve(ok, str, env) == -1)
			ft_execve_error(str);
		exit(0);
	}
	if (pid > 0)
		wait(&status);
}

int		is_builtin(char **str)
{
	if ((ft_strcmp(str[0], "cd")) == 0 ||
			(ft_strcmp(str[0], "env")) == 0 ||
			(ft_strcmp(str[0], "setenv")) == 0 ||
			(ft_strcmp(str[0], "unsetenv")) == 0 ||
			(ft_strcmp(str[0], "exit")) == 0)
		return (1);
	return (0);
}

void	which_builtin(char **str, t_env *e)
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

void	control(char **str, char **env, char *line, t_env *e)
{
	char	*ok;

	if ((ok = verify_access(str, e)) != NULL && (is_builtin(str)) != 1)
		execute_program(ok, str, env);
	else if (is_builtin(str) == 1)
		which_builtin(str, e);
	else if (str[0][0] == '.' && str[0][1] == '/')
		ft_executebin(str, env);
	else if (str[0][0] == '/' && str[0][1] != '\0')
		execute_program(str[0], str, env);
	else
		ft_putstr_fd(NOTFOUND, 2), ft_putendl_fd(line, 2);
}
