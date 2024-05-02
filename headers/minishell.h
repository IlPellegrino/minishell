/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:23:27 by nromito           #+#    #+#             */
/*   Updated: 2024/05/02 09:34:07 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>

typedef struct s_garbage
{
	void			*arg;
	struct s_garbage *next;
}		t_garbage;

typedef struct s_shell
{
		struct s_shell 	*next;
		char 			*path;
		char			**mat_input;
		char			*input;
		char			**envp;
		char			**path_env; 
		t_garbage  		*collector;
}		t_shell;


/* lexer */
char 	*lexer(t_shell *shell);

char	*ft_readline(char *str);

/* parsing */
int		find_path(t_shell *shell);

#endif