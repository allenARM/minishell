/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:52:25 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/16 17:52:26 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_return_val(t_list *pwd)
{
	char	*str;
	t_list	*tmp;

	str = ft_strnew(1);
	if (!pwd)
		str = ft_update(str, ft_strjoin(str, "/"));
	tmp = pwd;
	while (pwd)
	{
		str = ft_update(str, ft_strjoin(str, "/"));
		str = ft_update(str, ft_strjoin(str, pwd->name));
		pwd = pwd->next;
	}
	ft_list_clean(&tmp);
	return (str);
}

t_list	*remove_extra_path(t_list *pwd, char *address)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_strsplit(address, '/');
	while (arr[i])
	{
		if (!ft_strcmp(arr[i], ".."))
			ft_list_remove_back(&pwd);
		else if (!ft_strcmp(arr[i], "."))
		{
			i++;
			continue ;
		}
		else
			pwd = ft_list_add_back(pwd, arr[i]);
		i++;
	}
	ft_clean_arr(&arr);
	return (pwd);
}

char	*new_pwd(char *old_pwd, char *address)
{
	char	*str;
	int		i;
	t_list	*pwd;

	if (address && address[0] == '/')
		old_pwd = ft_update(old_pwd, ft_strnew(1));
	i = 0;
	pwd = NULL;
	address = ft_update(address, ft_strjoin("/", address));
	address = ft_update(address, ft_strjoin(&old_pwd[1], address));
	pwd = remove_extra_path(pwd, address);
	str = create_return_val(pwd);
	ft_strdel(&old_pwd);
	free(address);
	return (str);
}

void	argv_null(char *address, t_info *info)
{
	char *home;

	home = find_in_env("HOME", info);
	address = ft_update(address, ft_strdup(home));
	info->old_pwd = ft_strdup(info->pwd);
	info->pwd = ft_update(info->pwd, ft_strdup(home));
	chdir(address);
	ft_strdel(&address);
}

void	go_to_cd(char **argv, t_info *info)
{
	char	*address;

	address = ft_strnew(1);
	if (argv[1] == NULL || (argv[1] && !ft_strcmp(argv[1], "--")))
		argv_null(address, info);
	else if (argv[1] && argv[1][0] == '-' && ft_strlen(argv[1]) == 1)
	{
		address = ft_update(address, ft_strdup(info->old_pwd));
		ft_printf("%s\n", info->old_pwd);
		chdir(info->old_pwd);
		change_pwd(address, info);
	}
	else if (argv[2])
		ft_printf("cd: string not in pwd: %s\n", argv[1]);
	else if (chdir(argv[1]) == 0)
	{
		address = ft_update(address, ft_strdup(argv[1]));
		change_pwd(address, info);
	}
	else
	{
		free(address);
		ft_printf("minishell: No such file or directory\n");
	}
}
