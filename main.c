/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:16:41 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/02/07 15:14:40 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	ft_prompt(char **line)
{
	ft_putstr("minishell> ");
	get_next_line(0, line);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	char	**str;
	t_env	*e;

	e = (t_env *)malloc(sizeof(t_env));
	e->envcpy = env;
	if (argc == 1 && argv[0] != NULL)
	{
		while (42)
		{
			line = NULL;
			while ((line == NULL) || (line[0] == '\0'))
				ft_prompt(&line);
			line = ft_tabtospace(line);
			if (ft_is_space(line) == 0)
			{
				if ((str = ft_is_semicolon(line)) != NULL)
					ft_multiple_cmd(str, e);
				else
					ft_control(ft_strsplit(line, ' '), line, e);
			}
		}
	}
	return (0);
}
