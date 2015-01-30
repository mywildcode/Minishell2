/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 17:46:37 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/01/30 19:28:56 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

char	***ft_split_env(t_env *e, char c)
{
	int		i;
	char	***split_env;

	i = 0;
	split_env = (char ***)malloc(sizeof(char **) * 100);
	while (e->envcpy[i] != NULL)
	{
		split_env[i] = (char **)malloc(sizeof(char *) * 100);
		split_env[i] = ft_strsplit(e->envcpy[i], c);
		i++;
	}
	return (split_env);
}

void	ft_execve_error(char **str)
{
	if (str[0][0] == '.' && str[0][1] != '/')
		ft_putendl_fd(ARGUMENTS, 2);
	else if (str[0][0] == '/' || (str[0][0] == '.' && str[0][1] == '/' &&
				str[0][2] == '\0'))
		ft_putstr_fd(PERMISSION, 2), ft_putendl_fd(str[0], 2);
	else if ((str[0][0] == '/' && str[0][1] != '\0') || (str[0][0] == '.' &&
			str[0][1] == '/' && str[0][2] != '\0'))
		ft_putstr_fd(NOSUCHFILE, 2), ft_putendl_fd(str[0], 2);
	else
		ft_putstr_fd(PERMISSION, 2), ft_putendl_fd(str[0], 2);
}

char	*ft_new_var(char **str)
{
	char	*var;

	if (str[1] != NULL && str[2] == NULL)
	{
		var = (char *)malloc(sizeof(var) * ft_strlen(str[1]) + 2);
		var = ft_strjoin(str[1], "=");
	}
	else
	{
		var = (char *)malloc(sizeof(var) * ft_strlen(str[1]) +
				ft_strlen(str[2]) + 2);
		var = ft_strjoin(ft_strjoin(str[1], "="), str[2]);
	}
	return (var);
}

int		is_sh2(char *str, t_env *env)
{
	char		*line;
	char		*ptr;
	long int	i;

	i = 0;
	if ((ptr = strchr(str, ';')) != NULL)
	{
		line = (char *)malloc(sizeof(line) * (ptr - str) + 1);
		while (i < (ptr - str))
			line[i] = str[i], i++;
		if (is_pipe_redir(line) == 1)
			which_ops(line, env);
	}
	return (1);
}

int		is_pipe_redir(char *line)
{
	if (strchr(line, '|') != NULL || strstr(line, "<<") != NULL ||
			strstr(line, ">>") != NULL || strchr(line, '<') != NULL ||
			strchr(line, '>') != NULL)
		return (1);
	return (0);
}

void	which_ops(char *str, t_env *env)
{
	char	**str2;

	str2 = ft_strsplit(str, ' ');
	if (strchr(str, '|') != NULL)
		ft_pipe();
	return ;
}
