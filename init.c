/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:18:56 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/02/05 16:54:32 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int		ft_is_space(char *str)
{
	size_t		i;

	i = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

char	*ft_tabtospace(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 9)
			line[i] = 32;
		i++;
	}
	return (line);
}

char	**ft_is_semicolon(char *str)
{
	char	**line;

	if (strchr(str, ';') != NULL)
	{
		line = ft_strsplit(str, ';');
		return (line);
	}
	return (NULL);
}

int		ft_is_builtin(char **str)
{
	if ((ft_strcmp(str[0], "cd")) == 0 ||
			(ft_strcmp(str[0], "env")) == 0 ||
			(ft_strcmp(str[0], "setenv")) == 0 ||
			(ft_strcmp(str[0], "unsetenv")) == 0 ||
			(ft_strcmp(str[0], "exit")) == 0)
		return (1);
	return (0);
}

int		ft_is_pipe_redir(char *line)
{
	if (strchr(line, '|') != NULL || strstr(line, "<<") != NULL ||
			strstr(line, ">>") != NULL || strchr(line, '<') != NULL ||
			strchr(line, '>') != NULL)
		return (1);
	return (0);
}
