/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:23:27 by nromito           #+#    #+#             */
/*   Updated: 2024/05/05 13:49:49 by nromito          ###   ########.fr       */
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

typedef struct s_token
{
		char **index;
	
}		t_token;

typedef struct s_garbage
{
	void			*arg;
	struct s_garbage *next;
}		t_garbage;

typedef struct s_shell
{
		struct s_shell 	*next;
		char 			*path;
		char			*cmd_name;
		char			**mat_input;
		char			*input;
		char			**envp;
		char			**path_env; 
		t_garbage  		collector[10];
}		t_shell;


/* lexer */
char 	*lexer(t_shell *shell);

char	*ft_readline(char *str);
void	forker(t_shell *shell, char *input_args);

/* parsing */
int		find_path(t_shell *shell);

/* protected functions */
int		fork_p(void);
int		access_p(char *file, int mode);
void	wait_p(int *status);
void	pipe_p(int pipe_fds[2]);
void	execve_p(char *cmd_path, char **argv, char **envp);
void	ft_error(char *msg, int id);
void	close_fds(void);

#endif