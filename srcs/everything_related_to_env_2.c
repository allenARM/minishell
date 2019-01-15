/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   everything_related_to_env_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:50:53 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/15 13:50:54 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_info *info)
{
	t_env *tmp;

	tmp = info->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 3)\
		&& ft_strncmp(tmp->key, "OLDPWD", 3))
			ft_printf("%s=%s\n", tmp->key, tmp->val);
		else
		{
			if (!ft_strncmp(tmp->key, "PWD", 3))
				ft_printf("PWD=%s\n", info->pwd);
			if (!ft_strncmp(tmp->key, "OLDPWD", 3))
				ft_printf("OLDPWD=%s\n", info->old_pwd);
		}
		tmp = tmp->next;
	}
}

void	create_env(t_info *info)
{
	extern char		**environ;
	char			**tmp;
	int				i;

	i = 0;
	info->env = NULL;
	while (environ[i])
	{
		tmp = ft_strsplit(environ[i], '=');
		info->env = ft_env_add_back(info->env, tmp[0], tmp[1]);
		ft_clean_arr(&tmp);
		++i;
	}
	info->old_pwd = ft_strdup(find_in_env("OLDPWD", info));
	info->pwd = ft_strdup(find_in_env("PWD", info));
}

char	*find_in_env(char *find, t_info *info)
{
	int				i;
	t_env			*tmp;

	tmp = info->env;
	i = 0;
	while (tmp && ft_strncmp(tmp->key, find, ft_strlen(find)))
		tmp = tmp->next;
	if (tmp)
		return (tmp->val);
	return (NULL);
}

char	**move_list_into_array(t_env *env)
{
	char	**ret;
	t_env	*tmp;
	int		i;

	tmp = env;
	i = ft_env_size(env);
	ret = (char**)malloc(sizeof(char*) * (i + 1));
	i = 0;
	while (tmp)
	{
		ret[i] = ft_strdup(tmp->key);
		ret[i] = ft_update(ret[i], ft_strjoin(ret[i], "="));
		ret[i] = ft_update(ret[i], ft_strjoin(ret[i], tmp->val));
		i++;
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}
