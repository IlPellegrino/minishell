/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:59:59 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/25 11:42:40 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>

# define HEREDOC "\033[1;33m> \033[0m"
# define RED_ARROW "\033[1;31m-> "
# define GREEN_ARROW "\033[1;32m-> "
# define MINISHELL "\e[1;96mminishell\033[0m$ "
# define DQ 34
# define SQ 39
# define US 95
# define PIPE 124
# define JESUS 1
# define COMMAND 0
# define OPEN_ERR 1
# define SYNTAX 2

typedef struct s_cmd
{
	char	*pathname;
	char	**cmd_arg;
}			t_cmd;

typedef struct s_table
{
	char		*command;
	int			fd;
	int			pos;
	t_cmd		*cmd;
}			t_table;

typedef struct s_token
{
	char	**index;
	int		*mat_ind;
	char	*tokens;
	int		exp;
	char	*flag;
	int		wrd;
	int		start;
	int		*redirs;
	char	*temp_token;
}		t_token;

typedef struct s_garbage
{
	char				*arg;
	char				**mat;
	struct s_garbage	*next;
}			t_garbage;

typedef struct s_shell
{
	char		*path;
	char		**envp;
	char		**path_env;
	char		*new_input;
	char		*input;
	int			error;
	int			index;
	char		*cmd_name;
	int			sig_recived;
	int			n_pipes;
	int			len;
	char		*arrow;
	t_token		*tokens;
	t_garbage	*collector;
	t_table		*cmd_table;
}			t_shell;

/* close shell */
void		close_shell(t_shell *shell);
int			collect_garbage(t_shell *shell, char *arg, char **mat);
t_garbage	*new_node(char *arg, char **mat);
void		free_cmd_table(t_shell *shell);

/* signals */
void		get_signal(void);

/* builtins */
void		ft_echo(char **echo_mat);
int			ft_cd(char **cd_mat);
int			ft_pwd(void);
int			ft_export(char **export_mat, char **env);

/* lexer */
int			check_word(t_shell *shell, t_token *token, int quote);
void		choose_if(t_shell *shell, t_token *token, int (*i));
void		checker(t_shell *shell, t_token *token, int words);
void		setup_index(t_shell *shell, t_token *token, int *i);
int			quotes_reader(t_shell *shell, int i, int *k);
void		copy_in_quotes(t_shell *shell, t_token *token, int (*r), int quote);
void		write_word(t_shell *shell, t_token *token, int r, int i);
void		create_minor(t_shell *shell, t_token *token, int (*i));
void		create_major(t_shell *shell, t_token *token, int (*i));
void		create_pipe(t_shell *shell, t_token *token, int (*i));
void		create_word(t_shell *shell, t_token *token, int (*i));
int			check_quotes(t_shell *shell, int *i, int *words);
int			pipe_checker(t_shell *shell, int i, int *words);
int			check_space(t_shell *shell, int words, int (*i));
int			check_redirs(t_shell *shell, int words, int (*i));
int			count_wrds(t_shell *shell);
int			lexer(t_shell *shell);
void		checker(t_shell *shell, t_token *token, int words);
char		*ft_readline(char *str);

/* expander */
void		expand_value(t_shell *shell, t_token *token, char *input, int j);
void		expand_values(t_shell *shell, t_token *token);
char		*remove_quotes(t_shell *shell, t_token *token, int i);
char		*check_flag(t_token *token);
int			count_quotes(t_token *token);
void		is_heredoc(t_shell *shell, t_token *token, char *input, int j);

/* parsing */
int			tokenizer(t_shell *shell);
int			get_path(t_shell *shell);
int			parsing(t_shell *shell);
char		*remove_redir(t_token *token);
int			find_builtins(char *cmd);
int			parse_redirs(t_shell *shell);
int			ft_heredoc(char *eof);

/* parsing: cmd table */
int			init_cmd_table(t_shell *shell);
int			find_infile(int start, t_shell *shell);
int			find_outfile(int start, t_shell *shell);
int			find_cmd(t_shell *shell, int start, t_token *token, int found);

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
int			ft_error(t_shell *shell, int error_type, char *str);
int			is_redir(int c);

/*executor*/
int			executor(t_shell *shell);

/* utils */
int			find_space(char *index);
int			find_cmd_path(t_shell *shell, char *cmd, int pos);
void		print_matrix(char **mat);
int			init_structs(t_shell *shell, int argc, char **argv, char **envp);

#endif