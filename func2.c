/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:20:33 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/02/05 19:16:40 by ql-eilde         ###   ########.fr       */
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

char	**ft_strsplit_spe(char *str, char *split)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char **)malloc(sizeof(ret));
	ret[0] = (char *)malloc(sizeof(char) * 100);
	while (str[i] != split[0])
	{
		ret[0][j] = str[i], i++, j++;
		if (str[i] == split[1])
			break ;
	}
	ret[0][j] = '\0';
	j = 0, i++, i++;
	ret[1] = (char *)malloc(sizeof(char) * 100);
	while (str[i] != '\0')
		ret[1][j] = str[i], i++, j++;
	ret[1][j] = '\0';
	return (ret);
}
