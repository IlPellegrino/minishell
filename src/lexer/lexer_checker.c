/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:46:29 by nromito           #+#    #+#             */
/*   Updated: 2024/06/20 20:19:00 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_quote(t_shell *shell, int i, int quote)
{
	while (shell->input[++i] && shell->input[i] != quote)
		;
	if (shell->input[i] == quote)
		return (i);
	return (0);
}

int	check_word(t_shell *shell, t_token *token, int quote, int *r)
{
	if (shell->input[token->start + 1] == quote && !shell->input[token->start + 2] )
	{
		token->index[token->wrd][(*r)++] = shell->input[token->start];
		token->index[token->wrd][(*r)++] = shell->input[token->start + 1];
		token->index[token->wrd][(*r)] = 0;
		
		return (1);
	}
	
	if (shell->input[++token->start] == quote
		&& (shell->input[token->start + 1] == SPACE
			|| shell->input[token->start + 1] == TAB
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
	expand_values(shell, token);
	token->flag = check_flag(token);
	token->index[token->wrd] = remove_quotes(shell, token, count_quotes(token));
	token->wrd++;
}

void	choose_if(t_shell *shell, t_token *token, int (*i))
{
	if ((*i) != 0 && shell->input[(*i)] == PIPE
		&& shell->input[(*i) - 1] != SPACE
		&& shell->input[(*i) - 1] != TAB
		&& shell->input[(*i) - 1] != '>'
		&& (*i) != 0 && shell->input[(*i) - 1] != '<')
		create_word(shell, token, &(*i));
	else if ((*i) != 0 && shell->input[(*i)] == '<'
		&& shell->input[(*i) - 1] != SPACE
		&& shell->input[(*i) - 1] != TAB
		&& shell->input[(*i) - 1] != '>'
		&& shell->input[(*i) - 1] != PIPE)
		create_word(shell, token, &(*i));
	else if ((*i) != 0 && shell->input[(*i)] == '>'
		&& shell->input[(*i) - 1] != SPACE
		&& shell->input[(*i) - 1] != TAB
		&& shell->input[(*i) - 1] != PIPE
		&& shell->input[(*i) - 1] != '<')
		create_word(shell, token, &(*i));
}
