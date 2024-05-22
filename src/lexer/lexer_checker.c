/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:46:29 by nromito           #+#    #+#             */
/*   Updated: 2024/05/22 15:26:24 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// int	find_sq(t_shell *shell, int i)
// {
// 	i++;
// 	while (shell->input[i] != SQ && shell->input[i] != '\0')
// 		i++;
// 	if (shell->input[i] == '\0')
// 		close_shell(shell);
// 	else if (shell->input[i] == SQ)
// 		return (i);
// 	return (0);
// }

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

void	copy_in_quotes(t_shell *shell, t_token *token, int (*r), int quote)
{
	if (quote == DQ)
	{
		if (check_word(shell, token, DQ))
			return ;
		token->index[token->wrd][(*r)++] = shell->input[token->start - 1];
		while (shell->input[token->start] != DQ)
			token->index[token->wrd][(*r)++] = shell->input[token->start++];
		token->index[token->wrd][(*r)++] = shell->input[token->start];
	}
	else if (quote == SQ)
	{
		if (check_word(shell, token, SQ))
			return ;
		token->index[token->wrd][(*r)++] = shell->input[token->start - 1];
		while (shell->input[token->start] != SQ)
			token->index[token->wrd][(*r)++] = shell->input[token->start++];
		token->index[token->wrd][(*r)++] = shell->input[token->start];
	}
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

void	setup_index(t_shell *shell, t_token *token, int *i)
{
	if (shell->input[(*i)] == PIPE
		|| shell->input[(*i)] == '>' || shell->input[(*i)] == '<')
		choose_if(shell, token, &(*i));
	else if (shell->input[(*i)] != PIPE
		&& shell->input[(*i)] != '>' && shell->input[(*i)] != '<')
		create_word(shell, token, &(*i));
	if (shell->input[(*i)] == '<')
		create_minor(shell, token, &(*i));
	if (shell->input[(*i)] == '>')
		create_major(shell, token, &(*i));
	if (shell->input[(*i)] == PIPE)
		create_pipe(shell, token, &(*i));
	if (shell->input[(*i)] == SPACE)
		while (shell->input[(*i)] == SPACE && shell->input[(*i)] != '\0')
			(*i)++;
	if (shell->input[(*i)] != '\0')
		token->start = (*i) - 1;
}

void	checker(t_shell *shell, t_token *token, int words)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	token->wrd = 0;
	while (shell->input[i] == 32)
		i++;
	token->start = i - 1;
	while (token->wrd < words)
	{
		if (shell->input[i] == SQ || shell->input[i] == DQ)
			i = quotes_reader(shell, i, &k);
		else if ((shell->input[i] == SPACE) || (shell->input[i] == '\0')
			|| (shell->input[i] == PIPE) || (shell->input[i] == '>')
			|| (shell->input[i] == '<'))
			setup_index(shell, token, &i);
		else
			i++;
	}
	token->index[token->wrd] = NULL;
	print_matrix(token->index);
}
