/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:19:58 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/02/03 14:53:56 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

char	*ft_verify_access(char **str, t_env *e)
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

void	ft_executebin(char **str, char **env)
{
	char	*cpy;
	char	*bin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cpy = (char *)malloc(sizeof(char) * ft_strlen(str[0]) + 1);
	while (str[0][i] != '/')
		i++;
	i++;
	while (str[0][i] != '\0')
		cpy[j] = str[0][i], i++, j++;
	cpy[j] = '\0';
	bin = cpy, free(cpy), ft_execute_program(bin, str, env);
}

void	ft_execute_program(char *cmd, char **str, char **env)
{
	int		status;
	pid_t	pid;

	pid = fork();
	cmd = cmd;
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		if (execve(cmd, str, env) == -1)
			ft_execve_error(str);
		exit(0);
	}
	if (pid > 0)
		wait(&status);
}
