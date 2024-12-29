/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_through_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:11:41 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 21:25:37 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	peek_token(t_token *checker, int var_nbr, ...)
{
	va_list	ptr;
	int		flag;
	int		i;
	char	*token;
	char	*a;

	i = -1;
	flag = 1;
	if (!checker)
		return (0);
	token = checker->token;
	va_start(ptr, var_nbr);
	if (token[0] == '<' && token[1] == '<' && token[2] == '\0')
		return (0);
	while (++i < var_nbr)
	{
		a = va_arg(ptr, char *);
		flag = ft_strcmp(token, a);
		if (flag == 0 && (checker->placing == DEFAULT))
			return (1);
	}
	va_end(ptr);
	return (0);
}

int	peek_future_tokens_type(t_token *head, t_type type)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
