/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:09:58 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/28 08:24:54 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

typedef struct			s_pipe
{
	int					backup[3];
	int					fdin;
	int					fdout;
	int					file_num;
	int					*fds;
	int					*pids;
}						t_pipe;

typedef struct			s_cmd_list
{
	char				*data;
	char				**args;
	int					start;
	int					end;
	char				*line;
	int					p;
	char				redir;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}						t_cmd_list;

typedef struct			s_inc
{
	int					i;
	int					j;
}						t_inc;

typedef struct			s_cmds
{
	char				*oldpwd;
	char				*save_oldpwd;
	int					cd;
	int					minus;
	int					exp_oldp;
	int					num_pipe;
	int					ret;
	int					i;
	int					j;
	char				*tmp_d;
	char				*tmp1_d;
	char				tmp2_d[2];
	char				*arg_d;
	int					quote;
	char				**new_env;
	char				**env_sort;
	char				**cmp_tab;
	int					ignore;
	char				**cmd;
	int					counter;
	int					sep;
	char				**str;
	char				**envir;
	char				**env_line;
	char				*env_arg;
	char				*env_val;
	char				*cmd_line;
	char				*buff;
	char				*pwd;
	char				*join_arg;
	char				*line;
	int					exit_status;
	char				**split_cmd;
	char				**f_parse_line;
	t_inc				*inc;
	t_pipe				pipe;
	t_cmd_list			*cmd_list;
	int					allocated;
	int					ret_old;
	int					is_ret;
	int					exp_err;
	int					srch_dup;
	int					sv_pos;
	int					chk_if_eq;
}						t_cmds;

int						g_ret;
int						get_next_line(int fd, char **line);
void					parse_list_line(char **line_list, t_cmd_list *list,
t_cmds *cmds);
void					parse_line(char	**line, t_cmds *cmds);
t_cmd_list				*list_line_cmds(char *data);
t_cmd_list				*list_cmds(char *data);
void					add_front(t_cmd_list **head, t_cmd_list *new);
t_cmd_list				*get_cmd(t_cmds *cmds, t_cmd_list *head);
int						cmd_cd(t_cmd_list *list, t_cmds *cmds);
int						cmd_env(t_cmds *cmds, t_cmd_list *list);
int						cmd_pwd(t_cmds *cmds);
int						cmd_echo(t_cmd_list *list);
int						cmd_exit(t_cmd_list *list, t_cmds *cmds);
void					print_cmds(t_cmd_list *cmds);
int						cmd_export(t_cmd_list *list, t_cmds *cmds);
int						cmd_unset(t_cmd_list *list, t_cmds *cmds);
void					get_home_env(t_cmds **cmds);
char					**add_to_arr(char **arr, char *value, int opt);
char					**ft_envdup(char **arr);
char					**ft_setenv(char *var, char *path, char **env);
int						ft_getenv(char *name, char **env);
char					**ft_add_to_arr(char *value, char **arr);
char					**ft_get_arr(char *value, char **arr);
char					*ft_get_first(const char *s, int c);
pid_t					exec_child(t_cmds *cmds, t_cmd_list *list);
char					*get_bin_path(char *cmdfile, char **env);
void					check_cmd(t_cmds *cmds, t_cmd_list *list);
int						ft_arr_len(char **tab);
void					check_if_oldpwd(t_cmds *cmds, int *i);
void					ft_print_export(char **arr);
char					**ft_sort_exp(char **envr);
void					update_dup_export(t_cmd_list *list, t_cmds **cmds,
						int *i);
void					ft_init_stx_err(char **iscmd, t_cmds **cmds);
char					*ft_strcat(char *dest, char *src);
char					*parse_dollar(t_cmds *cmds, char **line_list);
char					*ft_remove_quotes(char *res);
void					check_for_quote(t_cmds **cmds, char **ln, int *i);
int						is_quote(int c);
char					**split_cmd(char const *str, char c, t_cmds *cmds);
int						quote_activer(int c, int quote);
int						handle_stx_err(char **ln, t_cmds *cmds);
int						check_redir(char **ln, t_cmds *cmds);
int						check_q(char **ln, t_cmds *cmds);
int						get_sy_err(t_cmds *cmds);
char					*ft_free_str(char *str);
char					**ft_free_arr(char **str);
void					free_cmd_list(t_cmds *cmds);
void					sig_handle(int sig);
void					exit_error(char *str, int status, t_cmds *cmds,
						t_cmd_list *list);
int						exec_cmds(t_cmds *cmds, t_cmd_list *list);
int						print_error(char *cmd, char *arg, int err);
t_cmd_list				*starting_execution(t_cmds *cmds, t_cmd_list *list);
void					exec_io_redi(t_cmds *cmds, t_cmd_list *list);
void					redir_fd_io(t_cmds *cmds);
void					close_pipes(int *fds, int num_pipe);
void					create_io_fds_cpy(int *fds);
int						*create_fds(t_cmd_list *list, int j, int *fds);
int						is_builtin(char *cmd);
int						*pipe_file_des(int num_pipe, int *fds);
void					save_file_des(int *fds);
t_cmd_list				*skip_redir(t_cmd_list *list);
int						get_num_pipes(t_cmd_list *cmds);
int						print_cd_error(char *str);
void					set_env_val(char **line_list, t_cmds **cmds, int *i,
						int *l);
void					manag_quotes_d(char **line_list, t_cmds **cmds, int *i,
						int *is_in_dq);
int						err_ret(t_cmd_list *list, t_cmds **cmds, int *r,
						int opt);
#endif
