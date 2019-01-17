/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:52:40 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/16 17:54:34 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***divide_commands(char **commands)
{
	char		***d_comm;
	int			i;

	i = 0;
	while (commands[i])
		++i;
	d_comm = (char ***)malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (commands[i])
	{
		d_comm[i] = ft_strsplit(commands[i], ' ');
		++i;
	}
	d_comm[i] = NULL;
	ft_clean_arr(&commands);
	return (d_comm);
}

void	clean_all_commands(char ****comm)
{
	int i;

	i = 0;
	while ((*comm)[i])
	{
		ft_clean_arr(&(*comm)[i]);
		i++;
	}
	free(*comm);
}

void	main_while_loop(t_info info)
{
	char			*line;
	char			**commands;
	char			***d_comm;

	rl_bind_key('\t', rl_complete);
	while (1)
	{
		commands = NULL;
		initialize_readline();
		line = readline(BLUE"$> " WHITE);
		if (!line)
			break ;
		add_history(line);
		if (ft_strstr(line, ";;") == NULL)
			commands = ft_strsplit(line, ';');
		else
		{
			ft_printf("minishell: parse error near `;;'\n");
			continue ;
		}
		commands = cleaning_matrix(&commands);
		d_comm = parse_with_args(commands);
		compare_to_commands(d_comm, &info);
		free(line);
	}
}

int		main(void)
{
	t_info			info;

	ft_bzero(&info, sizeof(t_info *));
	create_env(&info);
	ft_printf("%s", CLEAN);
	main_while_loop(info);
	return (0);
}
