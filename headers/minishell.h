/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:59:59 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/21 11:04:17 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>

# define RED_ARROW "\033[1;31m-> "
# define GREEN_ARROW "\033[1;32m-> "
# define MINISHELL "\e[1;96mminishell\033[0m$ "
# define DQ 34
# define SQ 39
# define PIPE 124
# define JESUS 1
# define COMMAND 0
# define PARSE 1
# define SYNTAX 2

typedef struct s_cmd
{
	char	*pathname;
	char	**cmd_arg;
}			t_cmd;

typedef struct s_table
{
	char		*command;
	int			pos;
	t_cmd		*cmd;
}			t_table;

typedef struct s_token
{
		char 	**index;
		int		*mat_ind;
		char	*tokens;
		int		exp;
		char	*flag;
		int		wrd;
		int		start;
		char	*temp_token;
}		t_token;

typedef struct s_garbage
{
	char				*arg;
	char				**mat;
	struct s_garbage 	*next;
}		t_garbage;

typedef struct s_shell
{
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
		int				sig_recived;
		int				n_pipes;
		char			*arrow;
		t_token			*tokens;
		t_garbage  		*collector;
		t_table			*cmd_table;
}		t_shell;

/* close shell */
void		close_shell(t_shell *shell);
int			collect_garbage(t_shell *shell, char *arg, char **mat);
t_garbage	*new_node(char *arg, char **mat);

/* signals */
void		get_signal();

/* lexer */
char 		*lexer(t_shell *shell);
int			count_wrds(t_shell *shell);
void		checker(t_shell *shell, t_token *token, int words);
char		*ft_readline(char *str);
/* expander */
void		expander(t_shell *shell, t_token *token);
void		expand_value(t_shell *shell, t_token *token);
char		*remove_quotes(t_shell *shell, t_token *token, int i);
char		*check_flag(t_token *token);
int			count_quotes(t_token *token);

/* parsing */
int			tokenizer(t_shell *shell);
int			get_path(t_shell *shell);
int			parsing(t_shell *shell);
char		*remove_redir(t_token *token);
/* parsing: count */
int			count_pipes(t_shell *shell, char *tokens);
int			count_redir(char *tokens);
/* parsing: cmd table */
int			init_cmd_table(t_shell *shell);
int			find_infile(int start, t_shell *shell, t_table *table);
int			find_outfile(int start, t_shell *shell, t_table *table);
int			find_cmd(int start, t_token *token, t_table *table);
/* parsing utils */
void		print_cmd_table(t_shell *shell, int len);
char		*remove_redir(t_token *token);

/* protected functions */
int			fork_p(void);
int			access_p(char *file, int mode);
void		wait_p(int *status);
void		pipe_p(int pipe_fds[2]);
void		execve_p(char *cmd_path, char **argv, char **envp);
void		close_fds(void);
int			ft_error(int error_type, char *str);
int			is_redir(int c);

/* utils */
int			find_space(char *index);
int			find_cmd_path(t_shell *shell, char *cmd);
void		print_matrix(char **mat);
int			init_structs(t_shell *shell);

#endif