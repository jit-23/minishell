/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:30:54 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/12/30 15:35:47 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_n(const char *exprt, int length)
{
	int		i;
	char	*name;

	i = 0;
	name = (char *)malloc(sizeof(char) * (length + 1));
	if (!name)
		return (NULL);
	while (i < length)
	{
		name[i] = exprt[i];
		i++;
	}
	name[length] = '\0';
	return (name);
}

char	*get_v(const char *exprt, int start, int length)
{
	int		i;
	char	*value;

	i = 0;
	value = (char *)malloc(sizeof(char) * (length + 1));
	while (i < length)
	{
		value[i] = exprt[start + i];
		i++;
	}
	value[length] = '\0';
	return (value);
}

int	divide_it(t_shell *sh, const char *exprt)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	name = NULL;
	value = NULL;
	while (exprt[i] && exprt[i] != '=')
		i++;
	name = get_n(exprt, i);
	if (!name)
		return (0);
	if (!exprt[i] || exprt[i] != '=')
		return (manage_var(sh, name, NULL), free(name), 0);
	value = get_v(exprt, i + 1, strlen(exprt) - (i + 1));
	if (!value)
		return (free(name), 9);
	manage_var(sh, name, value);
	free(name);
	free(value);
	return (0);
}

int	ft_export(t_shell *sh, t_exec *ex)
{
	int	i;

	i = 1;
	if (!ex->args[1])
		return (organized_export(sh), 0);
	while (ex->args[i])
	{
		if (check_export_str(ex->args[i]))
			return (ft_export_error_msg(sh, ex->args[i]), 1);
		if (ex->args[i])
			divide_it(sh, ex->args[i]);
		i++;
	}
	return (0);
}
