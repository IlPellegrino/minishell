# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nromito <nromito@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 16:23:10 by nromito           #+#    #+#              #
#    Updated: 2024/04/29 15:53:30 by nromito          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_PATH = libft/
LIBFT = libft/libft.a

HEADERS = headers/minishell.h

BUILT_IN = built-in/echo.c
EXECUTOR = executor/exec.c
EXPANDER = expander/exec.c
PARSER = parser/parsing.c
LEXER = lexer/readline.c
UTILS = utils/utils.c

SRCS = ${BUILT_IN} ${EXECUTOR} ${EXPANDER} ${PARSER} ${LEXER} ${UTILS}

OBJS = ${SRCS:.c=.o}

COMPILE = cc -g -Wall -Wextra -Werror -lreadline

RAINBOW = $(shell echo "red, orange, yellow, green, blue, indigo, violet")

all: ${NAME}

${NAME}: ${OBJS} ${HEADERS}
		make -C ${LIBFT_PATH}
		$(COMPILE) $(OBJS) $(LIBFT) -o $(NAME)
		@echo $(RAINBOW)"Minishell ready, execute to join"

%.o: %.c
		$(COMPILE) -c $< -o $@

clean:
		@rm -rf $(OBJS)
		@make -C $(LIBFT_PATH)
		@echo $(RAINBOW)"Successfully cleaned!""

fclean: clean
		@rm -rf $(NAME)
		@make -C $(LIBFT)
		@echo $(RAINBOW)"Successfully Fcleaned!""

re: fclean all

.PHONY: all clean fclean