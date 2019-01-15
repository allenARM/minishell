
INCLUDES = -Iincludes -Ilibft

SRCS =	srcs/minishell.c srcs/cleaning_input.c srcs/utils.c\
		srcs/compare_for_commands.c srcs/everything_related_to_env_1.c\
		srcs/manage_cd.c srcs/list_struct_operations.c srcs/env_struct_operations.c\
		srcs/everything_related_to_env_2.c

LIBFT = -L ./libft -lft

READLINE = -lreadline -ledit

OBJ		=	$(SRCS:.c=.o)

EXEC = minishell

RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;36m
RED_EXTRA = \033[1;31m
GREEN_EXTRA = \033[1;32m
BLUE_EXTRA = \033[1;36m

%.o:%.c
			@echo "$(GREEN) - Creating $(GREEN_EXTRA)$<...$(RESET)"
			@gcc -Wall -Wextra -Werror -c $< -o $@ $(INCLUDES) -g

all: $(EXEC)

$(EXEC): $(OBJ)
	@make -C libft
	@echo "$(GREEN)Compiling executable $(GREEN_EXTRA)$(EXEC)$(RESET)"
	@gcc -Wall -Wextra -Werror -o $(EXEC) $(OBJ) $(INCLUDE) $(LIBFT) $(READLINE) -g
	@echo "$(BLUE_EXTRA)$(EXEC)$(BLUE): Complete$(RESET)"

clean:
	@if [ -a "srcs/minishell.o" ]; then \
	echo "$(RED)Deleting objects for $(RED_EXTRA)$(EXEC)$(RESET)"; \
	/bin/rm -rf $(OBJ); \
	fi
	@make -C libft clean
	@echo "$(BLUE_EXTRA)clean$(BLUE): Complete$(RESET)"

fclean: clean
	@if [ -a "$(EXEC)" ]; then \
	echo "$(RED)Deleting executable $(RED_EXTRA)$(EXEC)$(RESET)"; \
	/bin/rm -f $(EXEC); \
	fi

	@make -C libft fclean
	@echo "$(BLUE_EXTRA)fclean$(BLUE): Complete$(RESET)"

re: fclean all

.PHONY: clean fclean re
