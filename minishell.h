/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:20:59 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/22 02:44:11 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/include/libft.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2


typedef struct		s_pipe
{
	int				**fd;
	pid_t			*pid;
	int				count_pipe;
	int				count_commands;
}					t_pipe;

typedef struct		s_mass
{
	void			*content;
	struct s_mass	*next;
	struct s_mass	*prev;
}					t_mass;

typedef struct		s_env
{
	char			*bin;
	int				shlvl;
	int				pwd;
	char			*oldpwd;
	char			*path;
	int				count_bin;
}					t_env;

typedef struct		s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}					t_sig;

typedef struct		s_mini
{
	t_pipe			pipe;
	t_mass			*head;
	t_mass			*head_x;
	t_env			var;
	char			*av;
	char			***mass3d;
	char			**env;
	char			**div_pipe;
	char			*tmp;
	int				ret;
	int				exit;
	char			*free_line;
	
	
	int				err_status;
	char			*err_message;
	int				fdout;
	int				fdin;
	int				*array_fdout;
	int				*array_fdin;
	char 			**command_elems;
	char 			**pipes;
	char 			**commands;

}					t_mini;

t_sig	g_sig;

/*INIT*/
void				ft_init_before_loop(t_mini *s, char *av);
void				ft_init_in_loop(t_mini *s);
int					init_list(t_mini *s, char **env);
int					init_list_x(t_mini *s, char **env);

int					exec_bin(t_mini *s, char **arr, char *command);
int					mini_bin(t_mini *s);
void				mini_cd(t_mini *s, char *exec, char *arg);
void				mini_pwd(t_mini	*s);
void				mini_pwd_1(t_mini *s);
void				mini_oldpwd(t_mini *s);
void				mini_echo(char **str, t_mini *s);
int					mini_exit(t_mini *s, char *exec, char *arg);
void				mini_env(t_mini *s);
void				mini_export(t_mini *s);
void				mini_unset(t_mini *s);
int					mini_pipes(t_mini *s);

/*ENV*/
void				ft_shlvl(t_mini *s);
void				get_pwd(t_mini	*s);

/*SIGNAL*/
void				init_signal(void);
void				sig_int(int signum);
void				sig_quit(int code);
void				exit_code(t_mini *s);

int					length_to_equal(t_mini *s, char *line);
char				*put_quotes(char *s1);
void				ft_error(char *error, int flag);
char				*mini_putnbr(int n);

t_mass				*my_lstnew(void *content);
void				my_lstadd_back(t_mass **lst, t_mass *new);
void				my_lstdelone(t_mass *lst, void (*del)(void *));
t_mass				*deletelem(t_mass *lst);
void				ft_list_sort(t_mass **lst);


//________________PARSER
void				ft_parser(t_mini *s, char *line, char **env);
char *make_substitute(char *command, t_mass **head, int counter, t_mini *s);
char				**ft_split_new(char const *s, char c);
int					ft_strlen_modif(const char *str);
void				sort_ft(t_mini *s, char **env1);
int					ft_isspace(char c);
char				*ft_strnjoin_char(char *s1, char c, int quantity);
char				*find_file_name(char *line, int position, int *len);
int find_symbol(char *str, char c, t_mini *s);
void				define_fd_in(t_mini *s, char *line);
void				define_fd_out(t_mini *s, char *line);
void				ft_sort_pipes(t_mini *s);
int					ft_arrlen(char **matrix);
char *extract_file_name(char *line, char redir, t_mini *s);
char	*ft_concat(char *str1, char *str2);

//parser/utils1
int 				skip_symbol(const char *str, int *symbol_count, char symbol);
int					is_quote(char symbol);
//parser/find_symbol
void				define_flag(int shield_count, int *flag);
//parser/parser1
void				paste_error(const char *str, t_mini *s);
#endif