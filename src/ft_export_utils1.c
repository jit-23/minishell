/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:54:21 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/30 15:35:42 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_var(t_shell *sh, char *a, char *c)
{
	t_env	*new;
	t_env	*last;

	new = sh->ev;
	while (new->next)
		new = new->next;
	last = new;
	new->next = malloc(sizeof(t_env));
	new = new->next;
	new->env_name = ft_strdup(a);
	if (!c)
		new->env_value = ft_strdup("");
	else
		new->env_value = ft_strdup(c);
	new->next = NULL;
	new->prev = last;
	new->index = -1;
	new->displayed = 0;
}

int	check_export_str(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '-' || str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	manage_var(t_shell *sh, char *name, char *value)
{
	if (search_var(sh, name))
		delete_var(sh, name);
	insert_var(sh, name, value);
}

void	ft_export_error_msg(t_shell *sh, char *msg)
{
	(void)sh;
	ft_putstr_fd(2, "export: ");
	ft_putstr_fd(2, msg);
	ft_putstr_fd(2, " : not a valid identifier\n");
	g_sign = 1;
}
