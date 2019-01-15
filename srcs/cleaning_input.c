/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:50:43 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/15 13:50:43 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_real_length(char *s)
{
	int len;

	len = ft_strlen(s);
	len--;
	while (s[len] == ' ' || s[len] == '\t')
		len--;
	return (len);
}

char	*cleaning_string(char *s)
{
	int		i;
	int		k;
	int		len;
	char	*ret;

	i = 0;
	k = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	len = find_real_length(s);
	ret = ft_strnew(4096);
	while (i <= len)
	{
		if (s[i] == ' ')
		{
			ret[k] = ' ';
			k++;
			while (s[i] == ' ')
				i++;
		}
		else
			ret[k++] = s[i++];
	}
	ret[k] = '\0';
	return (ret);
}

char	**cleaning_matrix(char ***commands)
{
	char	**arr;
	int		i;
	int		length;

	length = 0;
	while ((*commands)[length])
		++length;
	arr = (char **)malloc(sizeof(char *) * (length + 1));
	i = -1;
	while (++i < length)
		arr[i] = cleaning_string((*commands)[i]);
	arr[i] = NULL;
	ft_clean_arr(commands);
	return (arr);
}
