/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 00:35:18 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/24 01:43:00 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	read_open_quote(t_shell *shell, char **input, int quote)
{
	char	*after_quote;
	char	*temp;

	while (1)
	{
		g_sig_type = 1;
		after_quote = readline(OPEN_QUOTE);
		if (!after_quote)
			return (0);
		temp = ft_strdup(*input);
		*input = ft_strjoin(temp, after_quote);
		free(temp);
		collect_garbage(shell, *input, 0);
		collect_garbage(shell, after_quote, 0);
		if (check_close_quotes(after_quote, quote))
			break ;
		*input = append_newline(*input);
		collect_garbage(shell, *input, 0);
	}
	return (1);
}

int	open_quote(t_shell *shell, int quote)
{
	char	*temp;
	char	*input;
	int		saved_in;

	saved_in = dup(0);
	input = ft_strdup(shell->input);
	temp = ft_strdup(input);
	free(input);
	input = ft_strjoin(temp, "\n");
	collect_garbage(shell, input, 0);
	free(temp);
	if (!read_open_quote(shell, &input, quote))
	{
		return (handle_exit_err(shell, saved_in, quote));
	}	
	shell->input = ft_strdup(input);
	collect_garbage(shell, shell->input, 0);
	return (1);
}

int	parse_open(t_shell *shell)
{
	int	quote;

	quote = quote_is_open(shell->input);
	if (quote)
		return (open_quote(shell, quote));
	else if (pipe_is_open(shell->input))
		return (open_pipe(shell));
	return (1);
}