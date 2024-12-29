/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 06:42:43 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/28 06:06:31 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(2, sizeof(t_exec));
	if (!exec)
	{
		ft_putstr_fd(2, ":Error on malloc\n");
		return (NULL);
	}
	exec->type = _EXEC;
	return (exec);
}

t_pipe	*init_pipe(void)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pipe)
	{
		ft_putstr_fd(2, "error on malloc\n");
		return (NULL);
	}
	pipe->type = _PIPE;
	pipe->left = NULL;
	pipe->right = NULL;
	pipe->fd[0] = -1;
	pipe->fd[1] = -1;
	return (pipe);
}

t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = _REDIR;
	redir->cmd = NULL;
	redir->fd = -1;
	redir->file = NULL;
	redir->mode = -1;
	return (redir);
}
