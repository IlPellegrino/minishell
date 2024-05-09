# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 15:40:44 by nromito           #+#    #+#              #
#    Updated: 2024/05/08 15:09:22 by ciusca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
MANDATORY_SRCS = ft_matrix_len.c count_words.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
MANDATORY_OBJS = ${MANDATORY_SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}
HEADER = libft.h

all: ${NAME}

${NAME}: ${MANDATORY_OBJS}
	ar rc ${NAME} ${MANDATORY_OBJS}
	ranlib ${NAME}

bonus: ${BONUS_OBJS} ${MANDATORY_OBJS}
	ar rc ${NAME} ${BONUS_OBJS} ${MANDATORY_OBJS}

%.o: %.c ${HEADER}
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f ${MANDATORY_OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

# .PHONY: all clean fclean re bonus