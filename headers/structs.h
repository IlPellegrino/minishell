/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:08:46 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/24 16:00:10 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_exec
{
	int	fds[2];
	int	last_pid;
	int	saved_out;
	int	saved_in;
	int	inf_dup;
	int	out_dup;
}			t_exec;

typedef struct s_cmd
{
	char	*pathname;
	char	**cmd_arg;
}			t_cmd;

typedef struct s_export
{
	int		pos;
	int		old_pos;
	char	*old;
}			t_export;

typedef struct s_exp
{
	int		sq;
	int		dq;
	int		begin;
	int		len;
	int		pos;
	char	*res;
	char	*line;
	char	*final_str;
}			t_exp;

typedef struct s_token
{
	char	**index;
	int		*mat_ind;
	char	*tokens;
	int		exp;
	char	*flag;
	int		null_flag;
	int		wrd;
	int		start;
	int		*redirs;
	char	*temp_token;
}		t_token;

typedef struct s_table
{
	char			*command;
	char			**redirs;
	int				*fd;
	int				quotes;
	t_cmd			*cmd;
	struct s_token	*token;
}			t_table;

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
	int			saved_in;
	char		*input;
	int			error;
	int			index;
	char		*cmd_name;
	int			sig_recived;
	int			n_pipes;
	int			fd_h;
	int			len;
	char		*arrow;
	t_token		*tokens;
	t_garbage	*collector;
	t_table		*cmd_table;
	t_exec		*executor;
}			t_shell;

#endif