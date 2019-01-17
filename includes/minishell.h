/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelikia <amelikia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:50:53 by amelikia          #+#    #+#             */
/*   Updated: 2019/01/16 17:57:12 by amelikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BLUE  "\033[1;34m"
# define WHITE  "\x1B[39m"

typedef struct		s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}					t_env;

typedef struct		s_info
{
	char			*pwd;
	char			*old_pwd;
	t_env			*env;
}					t_info;

typedef struct		s_list
{
	char			*name;
	struct s_list	*next;
}					t_list;

char				**cleaning_matrix(char ***commands);
void				print_env(t_info *info);
int					check_if_empty(char *str);
void				compare_to_commands(char ***d_comm,\
	t_info *info);
t_env				*ft_env_remove_by_key(t_env *list,\
	char *key);
t_env				*ft_env_add_back(t_env\
	*list, char *s1, char *s2);
int					ft_env_size(t_env *root);
void				go_to_cd(char **argv, t_info *info);
char				*find_in_env(char *find, t_info *info);
t_list				*ft_list_add_back(t_list *list, char *dir);
void				ft_list_remove_back(t_list **list);
void				env_manage(char **var, t_info *info);
void				ft_list_clean(t_list **list);
void				create_env(t_info *info);
char				**move_list_into_array(t_env *env);
char				***find_tild(char ***commands,\
	t_info *info);
void				change_pwd(char *address, t_info *info);
char				*new_pwd(char *old_pwd, char *address);
void				initialize_readline(void);
void				clean_all_commands(char ****comm);
void				manage_dollar(char **args, t_info *info);
char				***parse_with_args(char **args);
int					ft_list_size(t_list *root);
void				print_command(char *path, char **argv, t_env *env);
char				*add_to_str(char *str, char c);
t_list				*clean_empty_elems(t_list *list);

#endif
