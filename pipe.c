/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:19:29 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/02/05 18:58:17 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	ft_pipe(char **str, t_env *env)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_run_pipe(ft_strsplit(str[0], ' '), ft_strsplit(str[1], ' '), env);
		exit(0);
	}
	if (pid > 0)
		wait(&status);
}

void	ft_run_pipe(char **cmd1, char **cmd2, t_env *env)
{
	pid_t		child;
	int			pdes[2];

	pipe(pdes);
	child = fork();
	if (child == -1)
		exit(0);
	if (child == 0)
	{
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		close(pdes[READ_END]);
		execve(ft_verify_access(cmd1, env), cmd1, env->envcpy);
		exit(0);
	}
	if (child > 0)
	{
		dup2(pdes[READ_END], STDIN_FILENO);
		close(pdes[WRITE_END]);
		wait(NULL);
		execve(ft_verify_access(cmd2, env), cmd2, env->envcpy);
	}
}
