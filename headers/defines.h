/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:08:42 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/25 11:39:07 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define BLACK        "\x1b[30m"
# define RED          "\x1b[31m"
# define GREEN        "\e[1;32m"
# define YELLOW       "\x1b[33m"
# define BLUE         "\x1b[34m"
# define MAGENTA      "\x1b[35m"
# define CYAN         "\x1b[36m"
# define WHITE        "\x1b[37m"

# define BOLD         "\x1b[1m"
# define ITALIC       "\x1b[3m"
# define UNDERLINE    "\x1b[4m"
# define RESET          "\x1b[0m"
# define JESUS 1
# define HEREDOC "\033[1;33m> \033[0m"
# define RED_ARROW "\e[1;91m➔\033[0m "
# define GREEN_ARROW "\e[1;92m➔\033[0m "

# define MINISHELL "\x1b[36m┌───(\x1b[0m\x1b[3mminishell\x1b[36m@\x1b[0m\x1b[3mUser\x1b[36m)-[\x1b[1m\x1b[4m\x1b[37m"

# define SECOND_PART "\x1b[36m]\n\001└─$ \002\x1b[0m"

# define RED_MINISHELL "\x1b[36m┌───(\x1b[0m\x1b[3mminishell\x1b[31m@\x1b[0m\x1b[3mUser\x1b[36m)-[\x1b[1m\x1b[4m\x1b[37m"

# define SECOND_RED "\x1b[36m]\n\001└─$ \002\x1b[0m"

# define EOF_ERROR "minishell: warning: here-document\
delimited by end-of-file (wanted `eof')"

# define OPEN_QUOTE "\x1b[4m\x1b[1m\x1b[35mOpen Quote \x1b[0m-> "
# define OPEN_PIPE  "\x1b[4m\x1b[1m\x1b[35mOpen Quote \x1b[0m-> "
# define HISTORY_FILE ".history"
# define DQ 34
# define SQ 39
# define US 95
# define PIPE 124
# define JESU
# define COMMAND 0
# define OPEN_ERR 1
# define IN_HEREDOC 1
# define SYNTAX 2
# define SIG_C 3
# define HERE_EOF 3
# define EXIT 4
# define UNSET 5
# define EXPORT 6
# define ENV 7
# define CD_DIR 8
# define CD_ARGS 9
# define BINARY 10
# define FOLDER 11
# define NOT_FOLDER 12
# define NO_PERMISSION 13
# define NO_FILE 14
# define CD_UNSET 15
# define QUOTE_ERR 16
# define PIPE_ERR 17
# define CORE_DUMPED 4

#endif