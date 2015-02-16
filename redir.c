/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 15:06:00 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/02/05 20:29:21 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	ft_simple_oi(char **str, t_env *e)
{
	int		fd;
	int		child;

	fd = open(str[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(0);
	child = fork();
	if (child == -1)
		exit(0);
	if (child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(ft_verify_access(ft_strsplit(str[0], ' '), e),
					ft_strsplit(str[0], ' '), e->envcpy);
		exit(0);
	}
	if (child > 0)
	{
		close(fd);
		wait(NULL);
	}
}

void	ft_simple_io(char **str, t_env *e)
{
	int		fd;
	int		child;

	fd = open(str[1], O_RDONLY);
	if (fd == -1)
		exit(0);
	child = fork();
	if (child == -1)
		exit(0);
	if (child == 0)
	{
		dup2(fd, STDIN_FILENO);
		execve(ft_verify_access(ft_strsplit(str[0], ' '), e),
				ft_strsplit(str[0], ' '), e->envcpy);
		exit(0);
	}
	if (child > 0)
	{
		close(fd);
		wait(NULL);
	}
}

void	ft_double_oi(char **str, t_env *e)
{
	int		fd;
	int		child;

	fd = open(str[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit(0);
	child = fork();
	if (child == -1)
		exit(0);
	if (child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(ft_verify_access(ft_strsplit(str[0], ' '), e),
				ft_strsplit(str[0], ' '), e->envcpy);
		exit(0);
	}
	if (child > 0)
	{
		close(fd);
		wait(NULL);
	}
}

void	ft_heredoc(char **line)
{
	ft_putstr("heredoc> ");
	get_next_line(0, line);
}

void	ft_double_io(char **str, t_env *e)
{
	int		child;
	char	*line;

	if ((child = fork()) == -1)
		exit(0);
	if (child == 0)
	{
		while (1)
		{
			line = NULL;
			while ((line == NULL) || (line[0] == '\0'))
				ft_heredoc(&line);
			if (strcmp(line, str[1]) == 0)
				break ;
		}
		execve(ft_verify_access(ft_strsplit(str[0], ' '), e),
				ft_strsplit(str[0], ' '), e->envcpy);
		exit(0);
	}
	if (child > 0)
		wait(NULL);
}
