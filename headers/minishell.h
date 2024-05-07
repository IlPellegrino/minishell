/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:23:27 by nromito           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/05/06 18:06:14 by ciusca           ###   ########.fr       */
=======
/*   Updated: 2024/05/06 18:13:05 by nromito          ###   ########.fr       */
>>>>>>> 3b5afb8031eea053bb6a921d4b38fe2978708d2e
=======
/*   Updated: 2024/05/07 16:06:26 by nromito          ###   ########.fr       */
=======
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:23:27 by nromito           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/07 16:54:43 by ciusca           ###   ########.fr       */
=======
/*   Updated: 2024/05/07 12:10:50 by ciusca           ###   ########.fr       */
>>>>>>> 91eb39e188b945c6239f54bcc719af818dfd1df9
>>>>>>> 70e60318b7042749678a47ee80fc9771a33d7166
>>>>>>> 38abf0c34da8dbdf5a9ed543e6f810bf1884571a
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


typedef struct s_cmd
{
	char 			*path;
	char 			**command_table;
	struct s_shell 	*shell;
}			t_cmd;


typedef struct s_token
{
		char 	**index;
<<<<<<< HEAD
		int		*mat_ind; 
		char	*tokens;
=======
		int		wrd;
		int		start;
>>>>>>> 38abf0c34da8dbdf5a9ed543e6f810bf1884571a
}		t_token;

typedef struct s_garbage
{
	void				*arg;
	int					flag;
	struct s_garbage 	*next;
}		t_garbage;

typedef struct s_shell
{
<<<<<<< HEAD
		struct s_shell 	*next;
		char			*infile;
		char 			*outfile;
		char			**redirect;
=======
>>>>>>> 70e60318b7042749678a47ee80fc9771a33d7166
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

<<<<<<< HEAD
/* signal */
=======
/* signals */
void		get_signal(void);

/* signals */
>>>>>>> 38abf0c34da8dbdf5a9ed543e6f810bf1884571a
void	get_signal(void);

/* lexer */
char 	*lexer(t_shell *shell);
int		count_input(t_shell *shell);
void	checker(t_shell *shell, t_token *token, int words);

char	*ft_readline(char *str);
void	forker(t_shell *shell, char *input_args);

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
<<<<<<< HEAD
int		find_cmd(t_shell *shell, char *cmd);
=======
>>>>>>> 38abf0c34da8dbdf5a9ed543e6f810bf1884571a
void	print_matrix(char **mat);

/* garbage collector */
void	garbage_collector(t_shell *shell);

#endif