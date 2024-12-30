/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 08:40:15 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/30 15:30:52 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	look_front_back(t_token *tmp, int fb)
{
	if (!tmp || tmp->type == PIPE)
		return (1);
	if (fb == 1)
	{
		while (tmp && tmp->type == SPACE_BAR)
		{
			tmp = tmp->next;
			if (!tmp || tmp->type == PIPE)
				return (1);
		}
	}
	else if (fb == 2)
	{
		while (tmp && tmp->type == SPACE_BAR)
		{
			tmp = tmp->prev;
			if (!tmp || tmp->type == PIPE || is_redir_type(tmp))
				return (1);
		}
	}
	return (0);
}

int	look_for_redir(t_token *tmp, int fb)
{
	if (tmp && ((is_redir_type(tmp) || tmp->type == PIPE)))
		return (1);
	if (fb == 1)
	{
		while (tmp && tmp->type == SPACE_BAR)
		{
			tmp = tmp->next;
			if (!tmp || is_redir_type(tmp))
				return (1);
		}
	}
	else if (fb == 2)
	{
		if (!tmp)
			return (0);
		while (tmp && tmp->type == SPACE_BAR)
		{
			tmp = tmp->prev;
			if (!tmp || is_redir_type(tmp))
				return (1);
		}
	}
	return (0);
}

int	check_pipe_sequence(t_token *token)
{
	while (token)
	{
		if ((token->type == PIPE && look_front_back(token->next, 1))
			|| (token->type == PIPE && look_front_back(token->prev, 2)))
		{
			ft_putstr_fd(2, "syntax error near unexpected token '|'\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}

int	is_redir_type(t_token *token)
{
	if (token && (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == HEREDOC || token->type == _APPEND))
		return (1);
	return (0);
}
