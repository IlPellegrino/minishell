/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:23:27 by nromito           #+#    #+#             */
/*   Updated: 2024/05/06 15:23:10 by ciusca           ###   ########.fr       */
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


# define MINISHELL "\033[0;36mminishell\033[0m$ "
# define DQ 34
# define SQ 39

typedef struct s_cmd
{
	char 			*path;
	char 			**command_table;
	char 			**cmd;
	struct s_shell 	*shell;
}			t_cmd;

typedef struct s_token
{
		char **index;
	
}		t_token;

typedef struct s_garbage
{
	void				*arg;
	int					flag;
	struct s_garbage 	*next;
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
		t_garbage  		*collector;
		t_cmd			*cmd;
}		t_shell;


/* lexer */
char 	*lexer(t_shell *shell);
int		quotes_checker(t_shell *shell);
void	checker(t_shell *shell);

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

/*utils*/

/* garbage collector */
void	garbage_collector(t_shell *shell);

#endif