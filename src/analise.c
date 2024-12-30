/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/30 04:37:04 by fde-jesu         ###   ########.fr       */
/*												                              */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_tokens(t_shell *shell, char *cmdl)
{
	t_placing	place;

	(void)cmdl;
	place = DEFAULT;
	shell->heredoc_flag = 0;
	analise_cmdl(shell, place, 0, shell->cmd_line);
	if (check_syntax(shell))
	{
		g_sign = 1;
		return (1);
	}
	refine_token_list(shell);
	return (0);
}

void	analise_terminal_input(t_shell *shell, char *cmdline)
{
	shell->cmd_line = ft_strtrim(shell->cmd_line, " ");
	if (cmdline[0] == '\0')
		return ;
	if (parse_tokens(shell, cmdline))
		return ;
	if (!shell->rl->official_head)
		return ;
	init_ast(shell);
	return ;
}

/*
void	print_tree(t_cmd *root)
{
	static int j;
	int i;
	t_exec *ex;
	t_redir *redir;
	t_pipe *pp;

	i = -1;
	if (root == NULL)
		return ;
	if (root->type == _EXEC)
	{
		ex = (t_exec *)root;
		while (ex->args[++i])
			printf("%d - args - %s\n", j, ex->args[i]);
		j++;
		printf("\n");
	}
	else if (root->type == _REDIR)
	{
		redir = (t_redir *)root;
		print_tree((t_cmd *)redir->cmd);
		printf("redir mode(%d)\nfile %s\n", redir->mode, redir->file);
	}
	else if (root->type == _PIPE)
	{
		pp = (t_pipe *)root;
		printf("%d pipe - | \n", j);
		j++;
		print_tree((t_cmd *)pp->left);
		print_tree((t_cmd *)pp->right);
	}
} */