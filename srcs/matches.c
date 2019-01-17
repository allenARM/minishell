/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matches.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:52:35 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/16 17:52:36 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_cmd[] = {
	"echo", "env", "setenv", "unsetenv", "cd", "pwd", "exit",
	"emacs", "vim", "mkdir", "rm", "ls", "rmdir", "clear",
	"locate", "touch", "man", "mv", "gcc", "cat", (char*)NULL
};

static char	*command_generator(const char *text, int state)
{
	static int	i;
	static int	len;
	char		*name;

	if (!state)
	{
		i = 0;
		len = ft_strlen(text);
	}
	while (g_cmd[i] && (name = g_cmd[i]))
	{
		i++;
		if (ft_strncmp(name, text, len) == 0)
			return (ft_strdup(name));
	}
	return ((char *)NULL);
}

static char	**ash_complition(const char *text, int start, int end)
{
	char **matches;

	matches = NULL;
	(void)end;
	if (start == 0)
		matches = rl_completion_matches(text, command_generator);
	return (matches);
}

void		initialize_readline(void)
{
	rl_readline_name = "minishell";
	rl_attempted_completion_function = ash_complition;
}
