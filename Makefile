# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 17:01:15 by ciusca            #+#    #+#              #
#    Updated: 2024/05/28 17:58:57 by ciusca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_PATH = libft/
LIBFT = libft/libft.a

HEADERS = headers/minishell.h

PROTECTED_FUNC_SRC = protected_functions.c protected_functions2.c
CLOSING_SRC = close_shell.c
BUILT_IN_SRC = echo.c cd.c pwd.c export.c env.c
EXECUTOR_SRC = exec.c
EXPANDER_SRC = expand_pid.c exp.c quotes_and_flag.c
PARSER_SRC = heredoc_utils.c parse_redirs.c ft_heredoc.c parsing_utils.c parsing.c tokenizer.c cmd_table.c find_redirs.c
LEXER_SRC = readline.c lexer_checker.c word_creation.c count_words.c
UTILS_SRC = utils.c utils2.c
SIGNAL_SRC = signals.c
MAIN	= minishell.c

PROTECTED_FUNC = $(addprefix protected_func/, $(PROTECTED_FUNC_SRC))
CLOSING = $(addprefix close_and_free/, $(CLOSING_SRC))
BUILT_IN = $(addprefix built-in/, $(BUILT_IN_SRC))
EXECUTOR = $(addprefix executor/, $(EXECUTOR_SRC))
EXPANDER = $(addprefix expander/, $(EXPANDER_SRC))
PARSER = $(addprefix parser/, $(PARSER_SRC))
LEXER = $(addprefix lexer/, $(LEXER_SRC))
UTILS = $(addprefix utils/, $(UTILS_SRC))
SIGNAL = $(addprefix signals/, $(SIGNAL_SRC))

SRCS = $(addprefix src/, $(MAIN) $(CLOSING) $(SIGNAL) ${BUILT_IN} $(PROTECTED_FUNC) ${EXECUTOR} ${EXPANDER} ${PARSER} ${LEXER} ${UTILS})

OBJS = ${SRCS:.c=.o}

SUPRRESSION = @valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ingore_readline.supp -s ./minishell

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
		@echo $(MAGENTA) "  __  __ _____ _   _ _____  _____ _    _ ______ _      _       " $(NONE)
		@echo $(RED)    " |  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |      " $(NONE)
		@echo $(YELLOW) " | \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |      " $(NONE)
		@echo $(GREEN)  " | |\/| | | | |     | | |  \___ \|  __  |  __| | |    | |      " $(NONE)
		@echo $(CYAN)   " | |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____  " $(NONE)
		@echo $(BLUE)   " |_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______| " $(NONE)
		@echo $(WHITE)  "                                                               " $(NONE)

sup: all
		@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp -s ./minishell
clean:
		@rm -rf $(OBJS)
		@make -C $(LIBFT_PATH) clean
		@echo $(GREEN)"Successfully cleaned!" $(NONE)

fclean: clean
		@rm -rf $(NAME)
		@make -C $(LIBFT_PATH) fclean
		@echo $(CYAN)"Successfully Fcleaned!" $(NONE)

re: fclean all

.PHONY: all clean fclean

.SILENT: