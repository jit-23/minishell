/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_first_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:17:33 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 12:17:24 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	analise_cmdl(t_shell *shell, t_placing place, int i, char *cmdl)
{
	while (cmdl[i])
	{
		if (cmdl[i] == '\'')
			i += handle_single_quotes_type(39, shell, &place);
		else if (cmdl[i] == '\"')
			i += handle_double_quotes_type(34, shell, &place);
		else if (cmdl[i] && is_space(cmdl[i]))
			i += get_space(cmdl, i, shell, place);
		else if (cmdl[i] && cmdl[i] == '$')
		{
			if (shell->heredoc_flag == 1)
				i += get_word(cmdl, i, shell, place);
			else if (shell->heredoc_flag == 0)
				i += get_env_var(cmdl, i, shell, place);
		}
		else if (cmdl[i] && cmdl[i] == '|' && place == 2)
			i += get_pipe(shell, place);
		else if (cmdl[i] && (cmdl[i] == '>' || cmdl[i] == '<'))
			i += get_redirect_var(cmdl, i, shell, place);
		else if (cmdl[i] && !special_char(cmdl[i]) && !is_space(cmdl[i]))
			i += get_word(cmdl, i, shell, place);
		else if (cmdl[i] && (cmdl[i] == '='))
			i += get_equal(shell, place);
	}
}

int	lstsize(t_env *lst)
{
	t_env	*temp;
	int		count;

	count = 0;
	temp = lst;
	if (!lst)
		return (0);
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}
