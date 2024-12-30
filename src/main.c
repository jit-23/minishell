/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:42 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/30 16:46:15 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_prompt(t_shell *shell)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 100);
	shell->prompt = ft_strjoin(dir, "$> ");
	shell->cmd_line = readline(shell->prompt);
	if (shell->cmd_line && shell->cmd_line[0] != 0)
		add_history(shell->cmd_line);
	free(dir);
}

void	get_path_env(t_shell *shell, char **envp)
{
	t_env	*ev;
	char	*strs;

	(void)envp;
	ev = NULL;
	strs = NULL;
	shell->path = NULL;
	ev = search_env_var(shell, "PATH");
	if (!ev)
	{
		shell->path = NULL;
		return ;
	}
	strs = ev->env_value;
	shell->path = ft_split(strs, ':');
}

void	init_shell(t_shell *shell, char **ev)
{
	shell->env = ev;
	shell->root = NULL;
	get_path_env(shell, ev);
	shell->prompt = NULL;
	shell->cmd_line = NULL;
	shell->token_list = NULL;
	shell->stop_iteration = false;
	shell->token_list = (t_lexer *)malloc(sizeof(t_lexer));
	shell->rl = (t_lexer *)malloc(sizeof(t_lexer));
	shell->token_list->head = NULL;
	shell->token_list->official_head = NULL;
	shell->rl->head = NULL;
	shell->rl->official_head = NULL;
	shell->ret = 0;
	shell->heredoc_tmp_file = 65;
	shell->heredoc_flag = 0;
	shell->no_exec = 0;
}

int	main(int ac, char **av, char **ev)
{
	t_shell	shell;

	(void)av;
	ft_memset(&shell, 0, sizeof(t_shell));
	if (ac != 1)
		return (ft_putstr_fd(2, "invalid number of arguments:"), 1);
	core_values(&shell, ev);
	while (1)
	{
		default_values(&shell, ev);
		if (shell.cmd_line)
			create_execute_tree(&shell, shell.cmd_line);
		else
			end_loop(&shell);
	}
	return (0);
}
