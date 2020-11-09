/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:22:59 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/09 13:17:29 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        print_tab(char **tab, FILE *f)
{
    int i;

    i = -1;
//  fprintf(f, "\n**ARGS Tab length = |%d|\n", tb_len(tab));
    if (!tab)
        fputs("\nARGS TAB is NULL\n", f);
    if (tab)
        while (tab[++i])
            fprintf(f, "\t\tARG[%d] = |%s|", i, tab[i]);
}

t_cmd_list       *get_head(t_cmd_list  *cmds)
{
    while (cmds && cmds->prev)
        cmds = cmds->prev;
    return (cmds);
}

void        print_cmds(t_cmd_list *cmds)
{
    FILE *f;

    f = fopen("debug", "w+");
    if (cmds == NULL)
        fputs("\nERROR: ==> cmds is NULL\n", f);
    while (cmds)
    {
        fprintf(f,"\n==> CMD=|%s|\n--------------------------\nARGS: ", cmds->data);
        print_tab(cmds->args, f);
        fprintf(f, "\n--------------------------\nStart=|%d|\tEnd=|%d|\tRedir=|%c|%d|\n===============================\n",
                    cmds->start, cmds->end, cmds->redir, cmds->redir);
        cmds = cmds->next;
    }
    fclose(f);
}
