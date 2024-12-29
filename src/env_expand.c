/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 00:04:43 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/07 23:48:07 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char *env_var)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	while (env_var[i] != '=')
		i++;
	i++;
	j = i;
	while (env_var[j])
		j++;
	val = ft_calloc((j - i) + 1, sizeof(char) * ((j - i) + 1));
	j = i;
	i = 0;
	while (env_var[j])
	{
		val[i] = env_var[j];
		i++;
		j++;
	}
	val[i] = '\0';
	return (val);
}

char	*get_name(char *env_var)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (env_var[j] != '=')
		j++;
	name = ft_calloc(j + 1, sizeof(char) * (j + 1));
	while (env_var[i] != '=')
	{
		name[i] = env_var[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

t_env	*new_env_node(char *env)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(4, sizeof(t_env));
	new_node->env_name = get_name(env);
	new_node->env_value = get_env_value(env);
	new_node->next = NULL;
	new_node->displayed = false;
	return (new_node);
}

static void	define_index(t_env *head)
{
	while (head)
	{
		head->index = -1;
		head = head->next;
	}
}

t_env	*expand_env(char **env)
{
	t_env	*ptr;
	t_env	*a;
	t_env	*head;
	int		i;

	i = -1;
	while (env[++i])
	{
		if (i == 0)
		{
			ptr = new_env_node(env[i]);
			head = ptr;
			ptr->prev = NULL;
		}
		else
		{
			ptr->next = new_env_node(env[i]);
			a = ptr;
			ptr = ptr->next;
			ptr->prev = a;
		}
	}
	ptr->next = NULL;
	define_index(head);
	return (head);
}
