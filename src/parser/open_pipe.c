/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 01:31:09 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/24 01:49:23 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	pipe_is_open(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			i++;
			while (ft_isspace(str[i]))
				i++;
			if (!str[i])
				return (1);
		}
	}
	return (0);
}

int	read_pipe(t_shell *shell)
{
	char	*after_pipe;
	char	*temp;
	char	*new_input;
	int		i;

	while (1)
	{
		i = 0;
		g_sig_type = 1;
		after_pipe = readline(OPEN_PIPE);
		if (!after_pipe)
			return (0);
		collect_garbage(shell, after_pipe, 0);
		while (ft_isspace(after_pipe[i]))
			i++;
		if (!*after_pipe || !after_pipe[i])
			continue ;
		temp = ft_strjoin(shell->input, after_pipe);
		new_input = ft_strtrim(temp, "\n");
		free(temp);
		shell->input = new_input;
		collect_garbage(shell, shell->input, 0);
		return (1);
	}
	return (1);
}

int	open_pipe(t_shell *shell)
{
	int		saved_in;

	saved_in = dup(0);
	if (!read_pipe(shell))
	{
		dup2(saved_in, 0);
		close(saved_in);
		if (g_sig_type == SIG_C)
		{
			shell->error = 130;
			g_sig_type = 42;
		}
		else
		{
			ft_error(shell, PIPE_ERR, 0);
			close_shell(shell);
		}
		return (0);
	}
	close(saved_in);
	return (1);
}
