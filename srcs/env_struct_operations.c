/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:50:48 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/15 13:50:49 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_env_size(t_env *root)
{
	int		i;
	t_env	*entity;

	i = 1;
	if (!root)
		return (0);
	if (root)
	{
		entity = root;
		while (entity)
			(entity = entity->next) && i++;
	}
	return (i);
}

void		assign_value(t_env *list, char *s2)
{
	if (s2)
		list->val = ft_strdup(s2);
	else
		list->val = ft_strnew(1);
}

t_env		*ft_env_add_back(t_env *list, char *s1, char *s2)
{
	t_env		*begining;
	t_env		*node;

	if (list == NULL)
	{
		list = (t_env *)malloc(sizeof(t_env));
		list->key = ft_strdup(s1);
		assign_value(list, s2);
		list->next = NULL;
		return (list);
	}
	node = (t_env *)malloc(sizeof(t_env));
	begining = list;
	node->next = NULL;
	node->key = ft_strdup(s1);
	assign_value(node, s2);
	while (list->next)
		list = list->next;
	list->next = node;
	return (begining);
}

void		free_node(t_env *list)
{
	free(list->key);
	free(list->val);
	free(list);
}

t_env		*ft_env_remove_by_key(t_env *list, char *key)
{
	t_env		*head;
	t_env		*tmp;

	head = list;
	if (!ft_strcmp(list->key, key))
	{
		tmp = list->next;
		free_node(list);
		return (tmp);
	}
	while (list && list->next && ft_strcmp(list->next->key, key))
		list = list->next;
	if (list && list->next && !ft_strcmp(list->next->key, key))
	{
		tmp = list->next;
		list->next = list->next->next;
		free_node(tmp);
	}
	else if (list && !ft_strcmp(list->key, key))
	{
		tmp = list;
		list->next = NULL;
		free_node(tmp);
	}
	return (head);
}
