/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_for_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:50:45 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/15 13:50:47 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_command(char *path, char **argv, t_env *env)
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

int			check_if_path_exists(char **p, char *path, \
				char **args, t_info *info)
{
	int		i;

	i = -1;
	while (p[++i])
	{
		ft_strclr(path);
		path = ft_strcat(path, p[i]);
		(args[0][0] == '/') ? 0 : ft_strcat(path, "/");
		path = ft_strcat(path, args[0]);
		if (access(path, F_OK) != -1)
		{
			print_command(path, args, info->env);
			i = -100;
			break ;
		}
	}
	ft_clean_arr(&p);
	ft_strdel(&path);
	if (i == -100)
		return (1);
	return (-1);
}

int			find_command(char **args, t_info *info)
{
	char	**p;
	char	*path;

	if (!find_in_env("PATH", info))
		return (-1);
	p = ft_strsplit(find_in_env("PATH", info), ':');
	path = ft_strnew(PATH_MAX);
	if (check_if_path_exists(p, path, args, info) == 1)
		return (0);
	return (-1);
}

void		search_through_commands(char ***d_comm, t_info *info, int i)
{
	if (!ft_strcmp(d_comm[i][0], "exit"))
	{
		ft_printf("%s", CLEAN);
		exit(0);
	}
	else if (!ft_strcmp(d_comm[i][0], "clear"))
		ft_printf("%s", CLEAN);
	else if (!ft_strcmp(d_comm[i][0], "env"))
		print_env(info);
	else if (!ft_strcmp(d_comm[i][0], "cd"))
		go_to_cd(d_comm[i], info);
	else if (!ft_strcmp(d_comm[i][0], "setenv") ||\
		!ft_strcmp(d_comm[i][0], "unsetenv"))
		env_manage(d_comm[i], info);
	else
	{
		if (access(d_comm[i][0], F_OK) != -1)
			print_command(d_comm[i][0], d_comm[i], NULL);
		else if (find_command(d_comm[i], info) == -1)
			ft_printf("%s: command not found\n", d_comm[i][0]);
	}
}

void		compare_to_commands(char ***d_comm, t_info *info)
{
	int		i;

	i = 0;
	d_comm = find_tild(d_comm, info);
	while (d_comm && d_comm[i] && d_comm[i][0])
	{
		if (check_if_empty(d_comm[i][0]) == 1)
		{
			++i;
			continue ;
		}
		search_through_commands(d_comm, info, i);
		++i;
	}
}
