# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 16:23:10 by nromito           #+#    #+#              #
#    Updated: 2024/05/02 09:35:51 by ciusca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_PATH = libft/
LIBFT = libft/libft.a

HEADERS = headers/minishell.h

BUILT_IN = built-in/echo.c
EXECUTOR = executor/exec.c
EXPANDER = expander/exp.c
PARSER = parser/parsing.c
LEXER = lexer/readline.c
UTILS = utils/utils.c
MAIN	= minishell.c

SRCS = $(addprefix src/, $(MAIN) ${BUILT_IN} ${EXECUTOR} ${EXPANDER} ${PARSER} ${LEXER} ${UTILS})

OBJS = ${SRCS:.c=.o}

COMPILE = cc -Wall -Wextra -Werror -g 

RED = "\033[1;31m"
GREEN = "\033[1;32m"
YELLOW = "\033[1;33m"
BLUE = "\033[1;34m"
MAGENTA = "\033[1;35m"
CYAN = "\033[1;36m"
WHITE = "\033[1;37m"
NONE = '\033[0m'

all: ${NAME}
%.o: %.c
		$(COMPILE) -I $(LIBFT_PATH) -c $< -o $@

${NAME}: ${OBJS} ${HEADERS}
		make -C ${LIBFT_PATH}
		$(COMPILE) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
		@echo "\n"
		@echo "  __  __ _____ _   _ _____  _____ _    _ ______ _      _       "
		@echo " |  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |      "
		@echo " | \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |      "
		@echo " | |\/| | | | |     | | |  \___ \|  __  |  __| | |    | |      "
		@echo " | |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____  "
		@echo " |_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______| "
		@echo "                                                               "
		@echo "                                                               "

clean:
		@rm -rf $(OBJS)
		@make -C $(LIBFT_PATH) clean
		@echo $(RAINBOW)"Successfully cleaned!"

fclean: clean
		@rm -rf $(NAME)
		@make -C $(LIBFT_PATH) fclean
		@echo $(RAINBOW)"Successfully Fcleaned!"

re: fclean all

.PHONY: all clean fclean

.SILENT: