/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:51:14 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/29 17:00:14 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_shell *sh, t_exec *ex)
{
	int	i;

	i = 0;
	while (ex->args[++i])
		delete_var(sh, ex->args[i]);
	g_sign = 0;
}

t_env	*search_env_var(t_shell *sh, char *env_var)
{
	t_env	*search;

	search = sh->ev;
	while (search && ft_strcmp(env_var, search->env_name))
		search = search->next;
	if (!search)
		return (NULL);
	return (search);
}

void	delete_var(t_shell *sh, char *env_var)
{
	t_env	*target;
	t_env	*prev;
	t_env	*next;

	target = search_env_var(sh, env_var);
	if (!target)
		return ;
	prev = target->prev;
	next = target->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(target->env_name);
	free(target->env_value);
	free(target);
	if (!prev)
		sh->ev = next;
}
