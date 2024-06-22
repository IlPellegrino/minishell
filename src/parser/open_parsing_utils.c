/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:48:21 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/22 19:16:24 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*quote_string(int quote)
{
	if (quote == DQ)
		return ("\"");
	return ("'");
}

char	*append_input(t_shell *shell, char *after_quote)
{
	char	*final_input;
	
	final_input = ft_strjoin(shell->input, after_quote);
	free(shell->input);
	shell->input = ft_strdup(final_input);
	collect_garbage(shell, final_input, 0);
	return (final_input);
}

void	append_newline(t_shell *shell, char *final_input)
{
	char	*temp;

	temp = ft_strdup(final_input);
	free(shell->input);
	shell->input = ft_strjoin(temp, "\n");
	free(temp);
}

char	*read_open_quote(t_shell *shell, char *prompt)
{
	char	*after_quote;

	after_quote = readline(prompt);
	if (!after_quote)
		return (0);
	rl_on_new_line();
	collect_garbage(shell, after_quote, 0);
	return (after_quote);
}

char	*init_open_quote(t_shell *shell, int quote)
{
	char	*temp;
	char	*prompt;

	temp = ft_strdup(shell->input);
	free(shell->input);
	shell->input = ft_strjoin(temp, "\n");
	free(temp);
	prompt = get_prompt(quote);
	collect_garbage(shell, prompt, 0);
	return (prompt);
}