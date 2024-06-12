/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:08:42 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/12 12:08:43 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define HEREDOC "\033[1;33m> \033[0m"
# define RED_ARROW "\e[1;91m➔\033[0m "
# define GREEN_ARROW "\e[1;92m➔\033[0m "
# define MINISHELL "\e[1;96mminishell\033[0m$ "
# define EOF_ERROR "minishell: warning: here-document\
delimited by end-of-file (wanted `eof')"
# define DQ 34
# define SQ 39
# define US 95
# define PIPE 124
# define JESUS 1
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
# define CORE_DUMPED 4

#endif