/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:52:30 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/16 20:23:28 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_dollar(char **args, t_info *info)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && ft_strlen(args[i]) > 1)
			args[i] = ft_update(args[i],\
				ft_strdup(find_in_env((&args[i][1]), info)));
		i++;
	}
}

t_list	*clean_empty_elems(t_list *list)
{
	t_list	*new;
	t_list	*tmp;

	tmp = list;
	new = NULL;
	while (list)
	{
		if (list->name && list->name[0] != '\0'\
		&& (ft_strlen(list->name) != 1 || list->name[0] != ' '))
			new = ft_list_add_back(new, list->name);
		list = list->next;
	}
	ft_list_clean(&tmp);
	return (new);
}
