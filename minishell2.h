/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ql-eilde <ql-eilde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 17:55:03 by ql-eilde          #+#    #+#             */
/*   Updated: 2015/02/07 15:11:08 by ql-eilde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include "libft/libft.h"
# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# define PATH_MAX 200
# define NOSUCHFILE "minishell: no such file or directory: "
# define NOTFOUND "minishell: command not found: "
# define PERMISSION "minishell: permission denied: "
# define ARGUMENTS ".: not enough arguments"
# define CDERROR "minishell: file couldn't be find or access not granted: "
# define TOOFEWARGS "minishell: too few arguments: unsetenv"
# define TOOMANYARGS "minishell: too many arguments: setenv"
# define BUFF_SIZE 4096
# define READ_END 0
# define WRITE_END 1

typedef struct		s_env
{
	char			**envcpy;
}					t_env;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_read
{
	int				size;
	int				index;
	char			*read;
	int				fd;
	struct s_read	*next;
}					t_read;

char				***ft_split_env(t_env *e, char c);
int					get_next_line(const int fd, char **line);
char				*ft_getenv(char **env, char *elem);
char				**ft_getpaths(char *elem);
char				*ft_verify_access(char **str, t_env *e);
void				ft_execute_program(char *cmd, char **str, char **env);
void				ft_executebin(char **str, char **env);
void				ft_cd(char **str, t_env *e);
void				ft_exit(void);
void				ft_env(t_env *e);
int					ft_len(t_env *e);
void				ft_setenv(t_env **e, char **str);
int					ft_setenv_modify(t_env *e, char **str);
void				ft_unsetenv(t_env *e, char **str);
int					ft_is_builtin(char **str);
void				ft_which_builtin(char **str, t_env *e);
void				ft_control(char **str, char *line, t_env *e);
void				ft_execve_error(char **str);
char				*ft_new_var(char **str);
char				**ft_is_semicolon(char *str);
int					ft_is_pipe_redir(char *line);
void				ft_which_ops(char *str, t_env *env);
void				ft_pipe(char **str, t_env *env);
void				ft_run_pipe(char **cmd1, char **cmd2, t_env *env);
int					ft_is_space(char *str);
char				*ft_tabtospace(char *line);
void				ft_simple_oi(char **str, t_env *e);
void				ft_simple_io(char **str, t_env *e);
void				ft_double_oi(char **str, t_env *e);
void				ft_double_io(char **str, t_env *e);
char				**ft_strsplit_spe(char *str, char *split);
void				ft_multiple_cmd(char **str, t_env *e);

#endif
