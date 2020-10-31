#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct	s_cmds
{
	char		**cmd;
	int			counter;
	char		**envir;
	char		**env_line;
	char		*arg;
	char		*buff;
	char		*pwd;
	char		**oldpwd;
	int			start;

}				t_cmds;


int		get_next_line(int fd, char **line);
void	erase_file_debug();
void	write_to_file(char *s, char *num, int end);
void	get_cmd(t_cmds *cmds);
void	cmd_cd(t_cmds *cmds);
void	cmd_env(t_cmds *cmds);
void	cmd_pwd();
void	cmd_echo();
void	cmd_exit();

#endif