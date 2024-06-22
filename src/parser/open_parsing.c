/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:16:59 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/22 19:58:19 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_pipe(t_shell *shell)
{
	char	*after_pipe;
	char	*new_input;
	char	*temp;

	while (1)
	{
		after_pipe = readline("pipe\e[1;32m->\033[0m ");
		rl_on_new_line();
		if (!after_pipe)
		{
			ft_error(shell, OPEN_PIPE, 0);
			close_shell(shell);
		}
		if (!*after_pipe)
			continue ;
		temp = ft_strjoin(shell->input, after_pipe);
		new_input = ft_strtrim(temp, "\n");
		free(temp);
		shell->input = new_input;
		collect_garbage(shell, shell->input, 0);
		break ;
	}
	lexer(shell);
	tokenizer(shell);
	return  (1);
}

int	check_closed(char *str, int c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count % 2);
}

int	is_open(char *str)
{
	int	i;
	int	sq;
	int	dq;

	dq = 0;
	sq = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == DQ && !sq)
			dq = 1;
		else if (str[i] == DQ && dq)
			dq = 0;
		else if (str[i] == SQ && !dq)
			sq = 1;
		else if (str[i] == SQ && sq)
			sq = 0;
	}
	if (sq)
		return (SQ);
	else if (dq)
		return (DQ);
	return (0);
}

int	get_open_quote(t_shell *shell, char *prompt, int quote)
{
	char	*after_quote;
	char	*final_input;

	while (1)
	{
		g_sig_type = 1;
		after_quote = read_open_quote(shell, prompt);
		if (!after_quote)
			return (0);
		final_input = append_input(shell, after_quote);
		if (check_closed(after_quote, quote))
			return  (1);
		append_newline(shell, final_input);
	}
	return (0);
}


int	open_quote(t_shell *shell)
{
	int		quote;
	char	*prompt;
	int		saved_in;

	if (!shell->input)
		return (0);
	saved_in = dup(0);
	quote = is_open(shell->input);
	if (!quote)
		return (0);
	prompt = init_open_quote(shell, quote);
	if (!get_open_quote(shell, prompt, quote))
	{
		dup2(saved_in, 0);
		shell->error = 130;
		if (g_sig_type == SIG_C)
			return (0);
		return (ft_error(shell, OPEN_QUOTE, quote_string(quote)));
	}
	lexer(shell);
	return (1);
}
