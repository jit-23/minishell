/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:30:16 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/30 15:21:38 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redir_sequence(t_token *token)
{
	while (token)
	{
		if ((is_redir_type(token) && look_for_redir(token->next, 1))
			|| (is_redir_type(token) && look_for_redir(token->prev, 2)))
		{
			ft_putstr_fd(2, "syntax error near unexpected token (redir):\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}

int	check_heredoc(t_token *token)
{
	while (token)
	{
		if (token->type == HEREDOC && !token->next)
		{
			ft_putstr_fd(2, "syntax error near unexpected token `newline'\n");
			return (1);
		}
		else if ((token->type == REDIR_OUT && !token->next)
			|| (token->type == REDIR_OUT && (token->next
					&& token->next->type == REDIR_OUT)))
		{
			ft_putstr_fd(2, "syntax error near unexpected token `newline'\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}

int	check_quote_pair(t_token *token)
{
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	while (token)
	{
		if (token->type == D_QUOTE && token->placing == DEFAULT)
			dquote++;
		else if (token->type == S_QUOTE && token->placing == DEFAULT)
			squote++;
		token = token->next;
	}
	if ((dquote % 2) != 0)
		return (ft_putstr_fd(2,
				"syntax error: uneven number of double quotes!\n"), 1);
	else if ((squote % 2) != 0)
		return (ft_putstr_fd(2,
				"syntax error: uneven number of squote quotes!\n"), 1);
	return (0);
}

int	check_syntax(t_shell *sh)
{
	t_token	*tmp;

	tmp = NULL;
	tmp = sh->token_list->official_head;
	if (check_pipe_sequence(tmp))
		return (1);
	tmp = sh->token_list->official_head;
	if (check_redir_sequence(tmp))
		return (1);
	tmp = sh->token_list->official_head;
	if (check_quote_pair(tmp))
		return (1);
	tmp = sh->token_list->official_head;
	if (check_heredoc(tmp))
		return (1);
	return (0);
}
