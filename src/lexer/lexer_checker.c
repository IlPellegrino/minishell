/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:46:29 by nromito           #+#    #+#             */
/*   Updated: 2024/05/23 10:34:07 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_quote(t_shell *shell, int i, int quote)
{
	i++;
	while (shell->input[i] != quote && shell->input[i] != '\0')
		i++;
	if (shell->input[i] == '\0')
		close_shell(shell);
	else if (shell->input[i] == quote)
		return (i);
	return (0);
}

int	check_word(t_shell *shell, t_token *token, int quote)
{
	if (shell->input[++token->start] == quote
		&& (shell->input[token->start + 1] == SPACE
			|| shell->input[token->start + 1] == '\0'
			|| shell->input[token->start + 1] == PIPE))
		return (1);
	return (0);
}

int	quotes_reader(t_shell *shell, int i, int *k)
{
	if (shell->input[i] == SQ)
	{
		(*k) = find_quote(shell, i, SQ);
		while (i <= (*k))
		{
			if (shell->input[++i] == SQ)
				return (++i);
		}
	}
	else if (shell->input[i] == DQ)
	{
		(*k) = find_quote(shell, i, DQ);
		while (i <= (*k))
		{
			if (shell->input[++i] == DQ)
				return (++i);
		}
	}
	return (i);
}

void	create_word(t_shell *shell, t_token *token, int (*i))
{
	int	r;

	r = 0;
	token->index[token->wrd]
		= ft_calloc(sizeof(char*), (*i) - token->start);
	if (!token->index[token->wrd])
		return ;
	write_word(shell, token, r, (*i));
	token->flag = check_flag(token);
	expand_values(shell, token);
	token->index[token->wrd] = remove_quotes(shell, token, count_quotes(token));
	token->wrd++;
}

void	choose_if(t_shell *shell, t_token *token, int (*i))
{
	if ((*i) != 0 && shell->input[(*i)] == PIPE
		&& shell->input[(*i) - 1] != SPACE
		&& shell->input[(*i) - 1] != '>'
		&& (*i) != 0 && shell->input[(*i) - 1] != '<')
		create_word(shell, token, &(*i));
	else if ((*i) != 0 && shell->input[(*i)] == '<'
		&& shell->input[(*i) - 1] != SPACE
		&& shell->input[(*i) - 1] != '>'
		&& shell->input[(*i) - 1] != PIPE)
		create_word(shell, token, &(*i));
	else if ((*i) != 0 && shell->input[(*i)] == '>'
		&& shell->input[(*i) - 1] != SPACE
		&& shell->input[(*i) - 1] != PIPE
		&& shell->input[(*i) - 1] != '<')
		create_word(shell, token, &(*i));
}
