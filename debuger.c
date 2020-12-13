// 	/* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
// /*   Updated: 2020/11/07 12:17:38 by elahyani         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <string.h>

// #define    BUFFER_SIZE 8

// typedef struct		s_cmd_list
// {
// 	char				*data;
// 	char				**args;
// 	int					start;
// 	int					end;
// 	char				*line;
// 	char				redir;
// 	struct s_cmd_list	*next;
// 	struct s_cmd_list	*prev;
// }					t_cmd_list;

// typedef struct	s_cmds
// {
// 	char		**cmd;
// 	int			counter;
// 	int			sep;
// 	char		**envir;
// 	char		**env_line;
// 	char		*env_arg;
// 	char		*env_val;
// 	char		*cmd_line;
// 	char		*buff;
// 	char		*pwd;
// 	char		*join_arg;
// 	char		*data;
// 	char		**split_cmd;
// 	t_cmd_list	*cmd_list;
// }				t_cmds;

// size_t		ft_strlen(const char *s)
// {
// 	size_t		i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// void	ft_putstr(char *s)
// {
// 	int i;

// 	if (s)
// 	{
// 		i = 0;
// 		while (s[i])
// 			putchar(s[i++]);
// 	}
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int		i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)s + i);
// 		i++;
// 	}
// 	if ((char)c == '\0')
// 		return ((char *)s + i);
// 	return (NULL);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*sub;
// 	size_t			j;
// 	size_t			s_len;

// 	j = 0;
// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (start > s_len)
// 		return (strdup(""));
// 	if (len > s_len - start)
// 		len = s_len - start;
// 	if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
// 		return (NULL);
// 	while (j < len)
// 	{
// 		sub[j] = s[start];
// 		start++;
// 		j++;
// 	}
// 	sub[j] = '\0';
// 	return (sub);
// }

// int		ft_strcmp(const char *s1, const char *s2)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while ((s1[i] || s2[i]))
// 	{
// 		if (s1[i] != s2[i])
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*join;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	if (!(join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
// 		return (NULL);
// 	while (s1[i])
// 		join[j++] = s1[i++];
// 	i = 0;
// 	while (s2[i])
// 		join[j++] = s2[i++];
// 	join[j] = '\0';
// 	return (join);
// }

// static char		**ft_free(char **split)
// {
// 	int		i;

// 	i = 0;
// 	while (split[i])
// 		free(split[i++]);
// 	free(split);
// 	return (NULL);
// }

// int			check_for_q(char *str, int j)
// {
// 	char	q;

// 	str += j;
// 	j = 0;
// 	q = *str;
// 	while (str[++j])
// 		if (str[j] == q && ((j && str[j - 1] != '\\') || !j))
// 			break ;
// 	if (str[j])
// 		return (j);
// 	return (-1);
// }

// static char		**ft_index(char **split, char *str, char x)
// {
// 	int i;
// 	int j;
// 	int k;
// 	int q;

// 	i = -1;
// 	k = 0;
// 	j = -1;
// 	q = -1;
// 	while (str[++i])
// 	{
// 		if (ft_strchr("\"'", str[i]) && ((i && str[i - 1] != '\\') || !i))
// 		{	j = i;
// 			i += check_for_q(str, i);
// 		}
// 		if (str[i] == x && j != -1)
// 		{
// 			if (!(split[k++] = ft_substr(str, j, i - j)))
// 				return (ft_free(split));
// 			j = -1;
// 		}
// 		else if (str[i] != x && j == -1)
// 			j = i;
// 	}
// 	if (j != -1)
// 		if (!(split[k] = ft_substr(str, j, i - j)))
// 			return (ft_free(split));
// 	return (split);
// }

// static int		len_wrd(char *str, char c)
// {
// 	int			i;
// 	int			start;
// 	int			len;

// 	i = 0;
// 	len = 0;
// 	start = 0;
// 	while (str[i])
// 	{
// 		if (ft_strchr("\"'", str[i]) && ((i && str[i - 1] != '\\') || !i))
// 			i += check_for_q(str, i);
// 		if (str[i] == c && ((i && str[i - 1] != '\\') || !i))
// 		{
// 			if (start == 1)
// 			{
// 				len++;
// 				start = 0;
// 			}
// 		}
// 		else if (str[i] != c)
// 			start = 1;
// 		i++;
// 	}
// 	if (start)
// 		len++;
// 	return (len);
// }

// char			**ft_split(char const *str, char c)
// {
// 	char		**res;
// 	size_t		len;
// 	int			i;
// 	int			j;

// 	j = 0;
// 	i = -1;
// 	len = 0;
// 	if (!str)
// 		return (NULL);
// 	len = len_wrd((char *)str, c);
// 	if (!(res = (char **)malloc(sizeof(char *) * (len + 1))))
// 		return (NULL);
// 	res = ft_index(res, (char *)str, c);
// 	// while (++i < (int)len)
// 	// 	res[i] = ft_strtrim(res[i], "\"'");
// 	if (!res)
// 		return (NULL);
// 	res[len] = 0;
// 	return (res);
// }
// // __________________________________________________________________
// int		ft_line(char *str)
// {
// 	int		i;

// 	i = -1;
// 	while (str[++i] && str[i] != '\n')
// 		;
// 	return (i);
// }

// int		free_err(char **line, char *buff, char *ptr)
// {
// 	if (*line)
// 		free(*line);
// 	if (buff)
// 		free(buff);
// 	if (ptr)
// 		free(ptr);
// 	return (-1);
// }

// char	*del(char *str, char *data)
// {
// 	if (str)
// 		free(str);
// 	str = data;
// 	return (str);
// }

// int		check_line(char **p, char **line)
// {
// 	int		i;
// 	char	*tmp;

// 	if (*p)
// 	{
// 		if (ft_strchr(*p, '\n'))
// 		{
// 			i = ft_line(*p);
// 			*line = del(*line, ft_substr(*p, 0, i));
// 			*p = del(*p, strdup(*p + i + 1));
// 			if (!(*line) || !(*p))
// 				return (free_err(line, NULL, *p));
// 			return (1);
// 		}
// 		else if (ft_strlen(*p))
// 		{
// 			if (!(tmp = (*line) ? ft_strjoin(*line, *p) : strdup(*p)))
// 				return (free_err(line, NULL, *p));
// 			*line = del(*line, tmp);
// 			*p = del(*p, NULL);
// 			return (0);
// 		}
// 		free(*p);
// 	}
// 	return (0);
// }

// int		get_next_line(int fd, char **line)
// {
// 	int			r;
// 	char		*tmp;
// 	char		*buff;
// 	static char	*ptr;

// 	if (fd < 0 || !line || read(fd, NULL, 0) < 0 ||
// 		!(tmp = malloc(sizeof(char *) * (BUFFER_SIZE + 1))))
// 		return (-1);
// 	*line = strdup("");
// 	while ((r = read(fd, tmp, BUFFER_SIZE)))
// 	{
// 		tmp[r] = '\0';
// 		if (!(buff = (ptr) ? ft_strjoin(ptr, tmp) : strdup(tmp)))
// 			return (free_err(line, buff, ptr));
// 		ptr = del(ptr, buff);
// 		free(tmp);
// 		if (ft_strchr(ptr, '\n'))
// 			break ;
// 		if (!(tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
// 			return (free_err(line, buff, ptr));
// 	}
// 	if (r == 0)
// 		free(tmp);
// 	return (check_line(&ptr, line));
// }
// // __________________________________________________________________


// t_cmd_list	*get_cmd(t_cmds *cmds, t_cmd_list *head)
// {
// 	while (head)
// 	{
// 		head->args = ft_split(head->data, ' ');
// 		puts("==========================");
// 		printf("cmd->args[0] = |%s|\n", head->args[0]);
// 		printf("cmd->args[1] = |%s|\n", head->args[1]);
// 		puts("==========================");
// 		// if (ft_strcmp(head->args[0], "cd") == 0)
// 		// 	cmd_cd(head);
// 		// else if (ft_strcmp(head->args[0], "echo") == 0)
// 		// 	cmd_echo(head);
// 		// else if (ft_strcmp(head->args[0], "pwd") == 0)
// 		// 	cmd_pwd(head);
// 		// // else if (ft_strcmp(head->args[0], "export") == 0)
// 		// // 	cmd_export();
// 		// // else if (ft_strcmp(head->args[0], "unset") == 0)
// 		// // 	cmd_unset();
// 		// else if (ft_strcmp(head->args[0], "env") == 0)
// 		// 	cmd_env(head);
// 		// else if (ft_strcmp(head->args[0], "exit") == 0)
// 		// 	cmd_exit();
// 		// else   
// 		// 	execve(head->args[0], head->args, cmds->envir);
// 		if (head->end)
// 		{
// 			printf("end ==> |%d|\n", head->end);
// 			break ;
// 		}
// 		head = head->next;
// 	}
// 	return (head);
// }

// t_cmd_list	*list_cmds(t_cmd_list *list, char *data, int k)
// {
// 	t_cmd_list	*head;

// 	if (!list)
// 		head = (t_cmd_list *)malloc(sizeof(t_cmd_list));
// 	else
// 		head = list;
// 	if (k)
// 		head->data = data;
// 	else
// 		head->line = data;
// 	head->next = head->next ? head->next : NULL;
// 	head->prev = list ? head->prev : NULL;
// 	head->start = list ? head->start : 0;
// 	head->end = list ? head->end : 0;
// 	head->redir = list ? head->redir : 0;
// 	return (head);
// }

// void	add_front(t_cmd_list **head, t_cmd_list *new)
// {
// 	new->prev = *head;
// 	new->next = (*head)->next ? (*head)->next : NULL;
// 	(*head)->next = new;
// 	*head = new;
// }

// void	update_list(t_cmd_list **head, t_cmd_list **next ,t_cmd_list *new)
// {
// 	new->prev = (*next)->prev;
// 	puts("------------------------------------");
// 	(*next)->prev = new;
// 	new->next = *next;
// 	if (new->prev != NULL)
// 	{
// 		//new->line = new->prev->line;
// 		new->prev->next = new;
// 	}
// 	else
// 		*head = new;
// }

// // char	*get_env_val(t_cmds *cmds, char *join_arg)
// // {
// // 	int		j;
// // 	int		k;

// // 	j = 0;
// // 	k = 0;
// // 	if (cmds->env_val)
// // 		free(cmds->env_val);
// // 	cmds->env_val = strdup(join_arg + 1);
// // 	while (cmds->envir[j] != NULL)
// // 	{
// // 		cmds->env_line = ft_split(cmds->envir[j], '=');
// // 		if (ft_strcmp(cmds->env_line[0], cmds->env_val) == 0)
// // 		{
// // 			k = 1;
// // 			return (cmds->env_line[1]);
// // 		}
// // 		j++;
// // 	}
// // 	if (k == 0)
// // 		return (cmds->join_arg);
// // 	return (NULL);
// // }

// // int		b_point(char *arg)
// // {
// // 	int i;

// // 	i = 0;
// // 	while (arg[++i])
// // 		if (ft_strchr("$\\\"';| ", arg[i]))
// // 			return (i);
// // 	return (i);
// // }
// // --------------------------------------------------------------------

// void	parse_line(char	**line, t_cmds *cmds)
// {	
// 	t_cmd_list *head;
// 	t_cmd_list *new_node;
// 	int		len;
// 	int		i;

// 	i = -1;
// 	cmds->cmd_line = *line;
// 	len = ft_strlen(*line);
// 	head = list_cmds(NULL, cmds->cmd_line, 0);
// 	while (++i <= len)
// 	{
// 		if ((*line)[i] == ';' || (*line)[i] == '\0')
// 		{
// 			if ((*line)[i] == ';')
// 			{
// 				(*line)[i] = '\0';
// 				add_front(&head, list_cmds(NULL, *line + i + 1, 0));
// 			}
// 		}
// 	}
// 	while (head->prev != NULL)
// 		head = head->prev;
// 	cmds->cmd_list = head;
// }

// // --------------------------------------------------------------------
// void	parse_list_line(char **line_list, t_cmd_list *list, t_cmds *cmds)
// {	
// 	int			len;
// 	int			i;
// 	int			l;
// 	char		*tmp;
// 	char		*tmp1;
// 	char		tmp2[2];
// 	char		*arg;
// 	t_cmd_list	*head;

// 	// tmp = NULL;
// 	// tmp1 = NULL;
// 	// i = -1;
// 	// len = ft_strlen(*line_list);
// 	// arg = strdup("");
// 	// while (++i <= len)
// 	// { 
// 	// 	if ((*line_list)[i] == '$')
// 	// 	{
// 	// 		l = b_point(*line_list + i);
// 	// 		cmds->join_arg = ft_substr(*line_list + i, 0, l);
// 	// 		cmds->env_val = get_env_val(cmds, cmds->join_arg);
// 	// 		tmp = ft_strjoin(arg, cmds->env_val);
// 	// 		(arg) ? free(arg) : 0;
// 	// 		arg = strdup(tmp);
// 	// 		i += l - 1;
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		tmp2[0] = (*line_list)[i];
// 	// 		tmp2[1] = '\0';
// 	// 		tmp1 = ft_strjoin(arg, tmp2);
// 	// 		(arg) ? free(arg) : 0;
// 	// 		arg = strdup(tmp1);
// 	// 	}
// 	// }
// 	// *line_list = strdup(arg);
// 	// (arg) ? free(arg) : 0;
// 	// (tmp) ? free(tmp) : 0;
// 	// (tmp1) ? free(tmp1) : 0;
// 	len = ft_strlen(*line_list);
// 	printf("LINE ==> |%s|\n", list->line);
// 	head = list_cmds(list, *line_list, 1);
// 	printf("DATA ==> |%s|\n", *line_list);
// 	i = -1;
// 	while (++i <= len)
// 	{
// 		printf("here %c\n", (*line_list)[i]);
// 		if ((*line_list)[i] == ';' || (*line_list)[i] == '\0')
// 		{
// 			if (!head->prev || (head->prev && head->prev->end))
// 				head->start = 1;
// 			head->end = 1;
// 			// if ((*line_list)[i] == ';' )
// 			// {
// 				// printf("semi =>>>>>>>>>>>    |%s|\n", *line_list + i + 1);
// 				// (*line_list)[i] = '\0';
// 				// add_front(&head, list_cmds(head->next, strdup(*line_list + i + 1), 1));
// 				//update_list(&head, &head->next, list_cmds(NULL, *(line_list) + i + 1, 1));
// 				break ;
// 			// }
// 			// else
// 			// 	head->next = NULL;
// 			// if ((*line_list)[i] == '\0')
// 		}
// 		else if ((*line_list)[i] == '|')
// 		{
// 			if (!head->prev || (head->prev && head->prev->end))
// 				head->start = 1;
// 			// if (head->next)
// 			// 	update_list(&head, &head->next, list_cmds(NULL, strdup(*line_list + i + 1), 1));
// 			// else
// 			(*line_list)[i] = '\0';
// 			t_cmd_list *new;
// 			new = list_cmds(NULL, strdup(*line_list + i + 1), 1);
// 			// printf("pipe next =>>>>>%s\n", head->next->line);
// 			// if (head->next->line)
// 			// 	new->next = head->next;
// 			add_front(&head, new);
// 			// printf("after pipe =>>>>>%s\n", *line_list);
// 			// printf("===================> %d %s\n", i, ft_substr(*line_list, j, i - 1));
// 			puts("----------------> here"); 
// 		}
// 		// else if ((*line_list)[i] == '<')
// 		// 	head->redir = '<';
// 		// else if ((*line_list)[i] == '>')
// 		// {
// 		// 	if ((*line_list)[i + 1] == '>')
// 		// 	{
// 		// 		head->redir = 'a';
// 		// 		i++;
// 		// 	}
// 		// 	else
// 		// 		head->redir = '>';
// 		// }
// 	}
	
// 	// while (head->prev != NULL)
// 	// 	head = head->prev;
// 	// head->line = head->next->line;
// 	// cmds->cmd_list = head;
// }

// int		main(int argc, char **argv, char **envp)
// {
// 	t_cmds	*cmds;
// 	t_cmd_list *list;
// 	char	*line;
// 	int		status;
// 	char	*tmp;

// 	cmds = (t_cmds *)malloc(sizeof(t_cmds));
// 	cmds->cmd_list = malloc(sizeof(t_cmd_list));
// 	list = malloc(sizeof(t_cmd_list));
// 	cmds->envir = envp;
// 	cmds->env_val = NULL;
// 	cmds->env_arg = NULL;
// 	list->line = NULL;
// 	ft_putstr("minishell>");
// 	// while ((status = get_next_line(0, &line)) > 0)
// 	// {
// 	// 	if (ft_strcmp(line, ""))
// 	// 	{
//   			line = strdup("echo a ; echo b | echo c ; echo d");
// 			parse_line(&line, cmds);
// 			list = cmds->cmd_list;
// 			while (list)
// 			{
// 				printf("***** LINE %s\n", list->line);
// 				if (!list->line)
// 					break ;
// 				parse_list_line(&list->line, list, cmds);
// 				list = get_cmd(cmds, list);
// 				if (list)
// 					list = list->next;
// 			}
// 			//print_cmds(cmds->cmd_list);
// 			free(line);
// 		// }
// 		// ft_putstr_fd("minishell>", 1);
// 	//}
// 	return (0);
// }

// // echo $PWD; echo $OLDPWD; cd .; pwd; echo $PWD; echo $OLDPWD
// // cd '' ; echo $PWD