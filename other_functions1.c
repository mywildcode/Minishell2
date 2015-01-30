/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 17:31:01 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/01/30 16:13:26 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

char	*ft_getenv(char **env, char *elem)
{
	size_t	i;

	i = 0;
	if (env == NULL || elem == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], elem, ft_strlen(elem)) == 0)
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

char	**ft_getpaths(char *elem)
{
	return (ft_strsplit(elem, ':'));
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
	bin = cpy, free(cpy), execute_program(bin, str, env);
}

int		ft_len(t_env *e)
{
	int		i;

	i = 0;
	while (e->envcpy[i] != NULL)
		i++;
	return (i);
}

int		ft_setenv_modify(t_env *e, char **str)
{
	int		found;
	char	***split;
	int		i;

	i = 0;
	split = ft_split_env(e, '=');
	if (str[1] != NULL)
	{
		while (split[i] != NULL &&
				(found = ft_strcmp(split[i][0], str[1])) != 0)
			i++;
		if (found == 0)
		{
			e->envcpy[i] = ft_new_var(str);
			return (1);
		}
	}
	else
	{
		ft_env(e);
		return (1);
	}
	return (0);
}
