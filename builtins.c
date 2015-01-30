/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 17:30:06 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/01/30 16:13:16 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void	ft_cd(char **str, t_env *e)
{
	char	*home;
	char	*pwd;
	char	buf[PATH_MAX + 1];
	char	*tmp;

	pwd = getcwd(buf, PATH_MAX + 1);
	tmp = ft_strjoin(ft_strjoin("OLDPWD", "="), pwd);
	e->envcpy[18] = ft_strdup(tmp);
	if (str[1] == NULL)
		home = ft_getenv(e->envcpy, "HOME"), chdir(home);
	else if (access(str[1], R_OK) == -1 || chdir(str[1]) != 0)
		ft_putstr_fd(CDERROR, 2), ft_putendl_fd(str[1], 2);
	pwd = getcwd(buf, PATH_MAX + 1);
	tmp = ft_strjoin(ft_strjoin("PWD", "="), pwd);
	e->envcpy[12] = ft_strdup(tmp);
}

void	ft_exit(void)
{
	exit(EXIT_SUCCESS);
}

void	ft_env(t_env *e)
{
	int		i;
	int		j;
	int		k;
	int		ret;
	char	***split;

	i = 0;
	j = 0;
	k = 0;
	ret = 0;
	split = ft_split_env(e, '=');
	while (split[j] != NULL && (ret = ft_strcmp(split[j][k], "PATH")) != 0)
		j++;
	k++;
	if (split[j][k] == NULL)
		ft_putstr_fd(NOTFOUND, 2), ft_putendl_fd("env", 2);
	else
		while (e->envcpy[i] != NULL && split[j][k] != NULL)
			ft_putendl(e->envcpy[i]), i++;
}

void	ft_setenv(t_env **e, char **str)
{
	char	**new_env;
	char	*tmp;
	int		j;
	int		a;

	j = 0;
	a = 0;
	new_env = (char **)malloc(sizeof(new_env) * ft_len(*e));
	if (ft_strchr(str[1], '=') == NULL)
	{
		while ((*e)->envcpy[j] != NULL)
			new_env[a] = (*e)->envcpy[j], a++, j++;
		tmp = ft_new_var(str);
		new_env[a] = ft_strdup(tmp);
		new_env[++a] = NULL;
		a = 0;
		while (new_env[a])
			(*e)->envcpy[a] = ft_strdup(new_env[a]), a++;
		free(tmp), free(new_env), (*e)->envcpy[a] = NULL;
	}
	else
		ft_putendl_fd("setenv: Syntax Error.", 2);
}

void	ft_unsetenv(t_env *e, char **str)
{
	int		i;
	int		j;
	int		ret;
	char	***split;

	j = 1;
	i = 0;
	while (str[j] != NULL && ft_strcmp(str[1], "PATH") != 0)
	{
		split = ft_split_env(e, '=');
		while (split[i] != NULL && (ret = ft_strcmp(split[i][0], str[j])) != 0)
			i++;
		if (ret == 0)
		{
			while (i < (ft_len(e) - 1))
				e->envcpy[i] = e->envcpy[i + 1], i++;
			e->envcpy[i] = NULL;
		}
		i = 0, j++;
	}
}
