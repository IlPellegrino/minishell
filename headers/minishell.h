/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:59:59 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/17 11:41:33 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defines.h"
# include "structs.h"
# include "includes.h"

extern int	g_sig_type;

/* close shell */
void		close_shell(t_shell *shell);
int			collect_garbage(t_shell *shell, char *arg, char **mat);
t_garbage	*new_node(char *arg, char **mat);
void		free_cmd_table(t_shell *shell);

/* signals */
void		get_signal(void);

/* builtins */
int			ft_env(char **env_mat, t_shell *shell);
int			ft_echo(char **echo_mat);
int			ft_cd(char **cd_mat, t_shell *shell);
int			ft_pwd(void);
int			it_exist(char *new_var, t_shell *shell);
int			ft_exit(char **exit_mat, t_shell *shell, pid_t pid);
int			ft_unset(char **unset_mat, t_shell *shell);

/*export only*/
int			ft_export(char **export_mat, t_shell *shell);
char		*create_plus_var(char *new_var, char *new_str);
void		change_var(char *new_var, t_shell *shell);
int			pick_old_var(char *s);
char		*create_var(char *new_var);
void		add_var(char *new_var, t_shell *shell);
int			it_exist(char *new_var, t_shell *shell);
int			count_len(char *str);
int			check_export(char *to_check, t_shell *shell);
char		*write_inside(char *result, char *new_var, t_export *export);
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
char		*create_new_var(t_shell *shell, char *input, int n);
char		*ft_getenv(const char *name, t_shell *shell);
char		*expand_pid(void);
int			find_expansion(char *temp, int *start);
char		*here_expand(t_shell *shell, char *str, int start);
char		*copy_str_exp(t_shell *shell, int count, int *start, char *str);
char		*copy_prev(char *str, int start);

/* parsing */
int			tokenizer(t_shell *shell);
int			get_path(t_shell *shell);
int			parsing(t_shell *shell);
char		*remove_redir(t_token *token);
int			find_builtins(char *cmd);
int			parse_redirs(t_shell *shell);
int			ft_heredoc(t_shell *shell, t_token *token, int i);
char		*get_after(char *str, char *new_str, int start);

/* expand heredoc*/
int			delete_heredoc(void);
char		*copy_expanded(char *expanded, char *final_line, int *j);
char		*expand_var(char *line, int *i);
int			find_len(char *line);
char		*expand_heredoc(t_shell *shell, char *line);

/* parsing: cmd table */
int			init_cmd_table(t_shell *shell);
int			find_outfile(t_table *table, int *fd_pos, int end, int j);
int			find_infile(t_table *table, t_token *token, int end, int *fd_pos);
int			is_cmd(t_token *token, int end);
int			count_pipes(char *str);
int			count_redirects(t_token *token, int end);
//int			find_infile(int start, t_shell *shell);
//int			find_outfile(int start, t_shell *shell);
//int			find_cmd(t_shell *shell, int start, t_token *token, int found);

/* parsing utils */
char		*remove_redir(t_token *token);
int			is_redir(int c);
char		*get_pathname(t_shell *shell, char *str);
char		*after_exp(char *expand, int len, t_shell *shell);
char		*here_expand(t_shell *shell, char *str, int start);

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
int			pipe_handler(t_shell *shell, int i, int pid);
int			is_builtin(char *str);
int			pipe_handler(t_shell *shell, int i, int pid);
int			perform_redir(t_shell *shell, int i);
void		reset_io(t_exec *exec);
int			not_binary(char *str);
int			is_folder(t_shell *shell, char *str);
int			no_permission(char *str);
int			validate_cmd(t_shell *shell, t_table *table);
/* utils */
int			find_space(char *index);
int			allocate_envp(t_shell *shell);
int			find_cmd_path(t_shell *shell, char *cmd, int pos);
void		print_matrix(char **mat);
int			init_structs(t_shell *shell, int argc, char **argv, char **envp);
void		sig_handle(t_shell *shell);
void		close_redirs(int *red, int len);

#endif