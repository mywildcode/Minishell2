/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 16:08:38 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/01/30 16:13:59 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	run_pipe(void)
{
	int const	READ_END = 0;
	int const	WRITE_END = 1;
	pid_t		child;
	char		*cmd1 = NULL;
	char		*cmd2 = NULL;
	char		*args1[3];
	char		*args2[3];
	int			pdes[2];

	cmd1 = "/bin/ls";
	args1[0] = cmd1;
	args1[1] = "-lF";
	args1[2] = NULL;

	cmd2 = "/bin/cat";
	args2[0] = cmd2;
	args2[1] = "-e";
	args2[2] = NULL;

	pipe(pdes);
	child = fork();
	if (child == 0)
	{
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		close(pdes[READ_END]);
		execve(cmd1, args1, NULL);
		exit(0);
	}
	if (child > 0)
	{
		dup2(pdes[READ_END], STDIN_FILENO);
		close(pdes[WRITE_END]);
		wait(NULL);
		execve(cmd2, args2, NULL);
	}
}

int		main(void)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		run_pipe();
		exit(0);
	}
	if (pid > 0)
		wait(&status);
}
