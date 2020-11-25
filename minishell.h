#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct		s_cmd_list
{
	char				*data;
	char				**args;
	int					start;
	int					end;
	
	char				redir;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}					t_cmd_list;

typedef struct	s_cmds
{
	int			index;
	int			rem;
	char		*oldpwd;
	int			cd;
	int			minus;
	char		**exp;
	int			exp_index;

	///////////////////////
	char		**cmd;
	int			counter;
	int			sep;
	char		**envir;
	char		**env_line;   //uninitialized
	char		*env_arg;
	char		*env_val;
	char		*cmd_line;
	char		*buff;
	char		*pwd;
	char		*join_arg;
	char		*data;
	char		**split_cmd;
	t_cmd_list	*cmd_list;
}				t_cmds;


int		get_next_line(int fd, char **line);
void	get_env(t_cmds *cmds);
void	get_cmd(t_cmds *cmds, t_cmd_list *head);
void	cmd_cd(t_cmd_list *list, t_cmds *cmds);
void	cmd_env(t_cmds *cmds);
void	cmd_pwd(t_cmds *cmds);
void	cmd_echo();
void	cmd_exit();
void	print_cmds(t_cmd_list *cmds);
void	cmd_export(t_cmd_list *list, t_cmds *cmds);
void	cmd_unset(t_cmd_list *list, t_cmds *cmds);

#endif