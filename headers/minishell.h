/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:59:59 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/07 22:14:04 by nromito          ###   ########.fr       */
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
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>


# define MINISHELL "\e[1;96mminishell\033[0m$ "
# define DQ 34
# define SQ 39
# define SPACE 32

typedef struct s_cmd
{
	char 			*path;
	char 			**command_table;
	struct s_shell 	*shell;
}			t_cmd;


typedef struct s_token
{
		char 	**index;
		int		*mat_ind; 
		char	*tokens;
		int		wrd;
		int		start;
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
		char			*infile;
		char 			*outfile;
		char			**redirect;
		char 			*path;
		char			*cmd_name;
		char			**mat_input;
		char			*input;
		char			**envp;
		char			**path_env;
		char			*new_input;
		t_token			tokens;
		t_garbage  		*collector;
		t_cmd			*cmd;
}		t_shell;


/* signals */
void	get_signal(void);

/* lexer */
char 	*lexer(t_shell *shell);
int		count_wrds(t_shell *shell);
void	checker(t_shell *shell, t_token *token, int words);

char	*ft_readline(char *str);
//void	forker(t_shell *shell, char *input_args);

/* parsing */
int		tokenizer(t_shell *shell);
int		get_path(t_shell *shell);
int		parsing(t_shell *shell);
/* protected functions */
int		fork_p(void);
int		access_p(char *file, int mode);
void	wait_p(int *status);
void	pipe_p(int pipe_fds[2]);
void	execve_p(char *cmd_path, char **argv, char **envp);
void	ft_error(char *msg, int id);
void	close_fds(void);

/*utils*/
int		find_cmd(t_shell *shell, char *cmd);
void	print_matrix(char **mat);

/* garbage collector */
void	garbage_collector(t_shell *shell);

#endif