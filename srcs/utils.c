/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:52:50 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/16 17:54:05 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***find_tild(char ***commands, t_info *info)
{
	char	*home;
	int		i;
	int		j;

	i = 0;
	while (commands[i] && commands[i][0])
	{
		j = 1;
		while (commands[i][j])
		{
			if (commands[i][j][0] == '~')
			{
				home = find_in_env("HOME", info);
				commands[i][j] = ft_update(commands[i][j], ft_strjoin(home\
				, &commands[i][j][1]));
			}
			j++;
		}
		i++;
	}
	return (commands);
}

void	change_pwd(char *address, t_info *info)
{
	free(info->old_pwd);
	info->old_pwd = ft_strdup(info->pwd);
	info->pwd = new_pwd(info->pwd, address);
}

void	print_command(char *path, char **argv, t_env *env)
{
	pid_t	pid;
	char	**execve_bitch;

	execve_bitch = move_list_into_array(env);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, execve_bitch) == -1)
			ft_printf("minishell: command not found: %s\n", path);
		exit(-1);
	}
	else if (pid == -1)
	{
		ft_printf("Unable to fork process\n");
		exit(-1);
	}
	if (pid >= 1)
		wait(&pid);
	ft_clean_arr(&execve_bitch);
}

char	*add_to_str(char *str, char c)
{
	char		*charecter;

	charecter = (char *)malloc(sizeof(char) * 2);
	charecter[0] = c;
	charecter[1] = '\0';
	str = ft_update(str, ft_strjoin(str, charecter));
	free(charecter);
	return (str);
}

int		check_if_empty(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] > ' ')
			return (0);
		++i;
	}
	return (1);
}
