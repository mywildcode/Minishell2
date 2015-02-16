/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 01:55:51 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/01/30 16:12:55 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell2.h"

static t_read		*ft_freeread(t_read *red, t_read *prev, t_read **start)
{
	if (!prev)
		*start = red->next;
	else
		prev->next = red->next;
	free(red->read);
	free(red);
	if (!prev)
		return (*start);
	else
		return (prev->next);
}

static t_read		*ft_newread(int fd)
{
	t_read			*red;
	void			*tmp;
	int				ret;

	if (!(red = (t_read *)malloc(sizeof(t_read))))
		return (NULL);
	if (!(tmp = malloc(sizeof(char) * BUFF_SIZE)))
	{
		free(red);
		return (NULL);
	}
	if ((ret = read(fd, tmp, BUFF_SIZE)) < 0)
	{
		free(red);
		free(tmp);
		return (NULL);
	}
	red->read = (char *)tmp;
	red->fd = fd;
	red->size = ret;
	red->next = NULL;
	red->index = 0;
	return (red);
}

static int			ft_print(int n, t_read **redtmp, t_read **s, char **l)
{
	char			*tmpstr;
	int				index;

	if (!redtmp[0])
		return (-1);
	index = redtmp[0]->index;
	if (n == -1 || !(tmpstr = (char *)malloc(sizeof(char) * (n + 1))))
		return (-1);
	*l = tmpstr;
	while (n--)
	{
		*tmpstr++ = redtmp[0]->read[index++];
		if (index == redtmp[0]->size)
		{
			redtmp[0] = ft_freeread(redtmp[0], redtmp[1], s);
			index = 0;
		}
	}
	*tmpstr = 0;
	if (!redtmp[0] || (index == redtmp[0]->size && redtmp[0]->size < BUFF_SIZE))
		return (0);
	redtmp[0]->index = index + 1;
	if (redtmp[0]->index == redtmp[0]->size)
		redtmp[0] = ft_freeread(redtmp[0], redtmp[1], s);
	return (1);
}

static int			ft_findendl(int fd, t_read *red)
{
	int				index;
	int				size;
	t_read			*tmplst;

	size = 0;
	index = red->index;
	while (red->read[index] != '\n' && index < red->size)
	{
		index++;
		size++;
		if (index == red->size && red->size == BUFF_SIZE)
		{
			if (!(tmplst = ft_newread(fd)))
				return (-1);
			tmplst->next = red->next;
			red->next = tmplst;
			red = tmplst;
			index = 0;
		}
	}
	return (size);
}

int					get_next_line(const int fd, char **line)
{
	static t_read	*start = NULL;
	t_read			**redtmp;

	redtmp = malloc(sizeof(t_read *) * 2);
	if (fd < 0)
		return (-1);
	redtmp[1] = NULL;
	if (!start)
		start = ft_newread(fd);
	redtmp[0] = start;
	while (redtmp[0]->fd != fd)
	{
		if (!(redtmp[0]->next))
			redtmp[0]->next = ft_newread(fd);
		redtmp[1] = redtmp[0];
		redtmp[0] = redtmp[0]->next;
	}
	if (!redtmp[0] || !start)
		return (-1);
	return (ft_print(ft_findendl(fd, redtmp[0]), redtmp, &start, line));
}
