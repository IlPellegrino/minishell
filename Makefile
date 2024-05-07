# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 16:23:10 by nromito           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/05/07 14:19:39 by ciusca           ###   ########.fr        #
=======
<<<<<<< HEAD
#    Updated: 2024/05/06 17:51:32 by ciusca           ###   ########.fr        #
=======
#    Updated: 2024/05/07 12:11:32 by ciusca           ###   ########.fr        #
>>>>>>> 70e60318b7042749678a47ee80fc9771a33d7166
>>>>>>> 38abf0c34da8dbdf5a9ed543e6f810bf1884571a
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_PATH = libft/
LIBFT = libft/libft.a

HEADERS = headers/minishell.h

PROTECTED_FUNC = protected_func/protected_functions.c
BUILT_IN = built-in/echo.c
EXECUTOR = executor/exec.c
EXPANDER = expander/exp.c
PARSER = parser/parsing.c parser/tokenizer.c
LEXER = lexer/readline.c lexer/lexer_checker.c
UTILS = utils/utils.c
<<<<<<< HEAD
SIGNALS = signals/signals.c
MAIN	= minishell.c

SRCS = $(addprefix src/, $(SIGNALS) $(MAIN) ${BUILT_IN} $(PROTECTED_FUNC) ${EXECUTOR} ${EXPANDER} ${PARSER} ${LEXER} ${UTILS})
=======
SIGNAL = signals/signals.c
MAIN	= minishell.c

SRCS = $(addprefix src/, $(MAIN) $(SIGNAL) ${BUILT_IN} $(PROTECTED_FUNC) ${EXECUTOR} ${EXPANDER} ${PARSER} ${LEXER} ${UTILS})
>>>>>>> 70e60318b7042749678a47ee80fc9771a33d7166

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
		@echo $(MAGENTA) "  __  __ _____ _   _ _____  _____ _    _ ______ _      _       " $(NONE)
		@echo $(RED)    " |  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |      " $(NONE)
		@echo $(YELLOW) " | \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |      " $(NONE)
		@echo $(GREEN)  " | |\/| | | | |     | | |  \___ \|  __  |  __| | |    | |      " $(NONE)
		@echo $(CYAN)   " | |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____  " $(NONE)
		@echo $(BLUE)   " |_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______| " $(NONE)
		@echo $(WHITE)  "                                                               " $(NONE)

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