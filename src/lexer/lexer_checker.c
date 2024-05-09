/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:46:29 by nromito           #+#    #+#             */
/*   Updated: 2024/05/09 17:32:42 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_quotes(t_shell *shell, int i, int *words)
{
	if (shell->input[i] == DQ)
	{
		while (shell->input[++i] != DQ)
			;
		if (shell->input[++i] == '\0' || shell->input[i] == PIPE)
		{
			(*words)++;
			return (i);
		}
	}
	else if (shell->input[i] == SQ)
	{
		while (shell->input[++i] != SQ)
			;
		if (shell->input[++i] == '\0' || shell->input[i] == PIPE)
		{
			(*words)++;
			return (i);
		}
	}
	return (i);
}

int	pipe_checker(t_shell *shell, int i, int *words)
{
	if (shell->input[i + 1] != SPACE && shell->input[i - 1] != SPACE)
		(*words)++;
	return (++i);
}

int	check_space(t_shell *shell, int words, int (*i))
{
	if (shell->input[(*i) - 1] != PIPE)
		words++;
	while (shell->input[++(*i)] == SPACE)
		;
	return (words);
}

int	count_wrds(t_shell *shell)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (shell->input[i] == SPACE)
		i++;
	while (shell->input[i] != '\0')
	{
		if (shell->input[i] == DQ || shell->input[i] == SQ)
			i = check_quotes(shell, i, &words);
		else if (shell->input[i] == SPACE)
			words = check_space(shell, words, &i);
		else if (shell->input[i] == PIPE)
		{
			if (shell->input[i++ + 1] != PIPE)
				words++;
		}
		else if (shell->input[++i] == '\0' || shell->input[i] == PIPE)
			words++;
	}
	printf("words = %d\n", words);
	return (words);
}

int	find_sq(t_shell *shell, int i)
{
	i++;
	while (shell->input[i] != SQ && shell->input[i] != '\0')
		i++;
	if (shell->input[i] == '\0')
		ft_error(NULL, 40);
	else if (shell->input[i] == SQ)
		return (i);
	return (0);
}

int	find_dq(t_shell *shell, int i)
{
	i++;
	while (shell->input[i] != DQ && shell->input[i] != '\0')
		i++;
	if (shell->input[i] == '\0')
		ft_error(NULL, 40);
	else if (shell->input[i] == DQ)
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

void	create_word(t_shell *shell, t_token *token, int r, int i)
{
	while (++token->start < i)
	{
		if (shell->input[token->start] == DQ)
		{
			if (check_word(shell, token, DQ))
				break ;
			while (shell->input[token->start] != DQ)
				token->index[token->wrd][r++] = shell->input[token->start++];
		}
		else if (shell->input[token->start] == SQ)
		{
			if (check_word(shell, token, SQ))
				break ;
			while (shell->input[token->start] != SQ)
				token->index[token->wrd][r++] = shell->input[token->start++];
		}
		else
			if (shell->input[token->start] != '\0')
				token->index[token->wrd][r++] = shell->input[token->start];
	}
}

int	quotes_reader(t_shell *shell, int i, int *k)
{
	if (shell->input[i] == SQ)
	{
		(*k) = find_sq(shell, i);
		while (i <= (*k))
		{
			if (shell->input[++i] == SQ)
				return (++i);
		}
	}
	else if (shell->input[i] == DQ)
	{
		(*k) = find_dq(shell, i);
		while (i <= (*k))
		{
			if (shell->input[++i] == DQ)
				return (++i);
		}
	}
	return (i);
}

void	create_pipe(t_shell *shell, t_token *token, int (*i))
{
	int	r;
	int	pipe_nbr;

	r = 0;
	pipe_nbr = 0;
	while (shell->input[(*i)] == PIPE)
	{
		pipe_nbr++;
		(*i)++;
	}
	token->index[token->wrd] = ft_calloc(sizeof (char), pipe_nbr + 1);
	if (!token->index[token->wrd])
		return ;
	while (pipe_nbr-- > 0)
		token->index[token->wrd][r++] = '|';
	token->wrd++;
}

void	setup_index(t_shell *shell, t_token *token, int *i)
{
	int	r;

	r = 0;
	if ((shell->input[(*i) - 1] != SPACE
			&& shell->input[(*i)] == PIPE && (*i) != 0)
		|| (shell->input[(*i)] != PIPE))
	{
		token->index[token->wrd]
			= ft_calloc(sizeof(char), (*i) - token->start + 1);
		if (!token->index[token->wrd])
			return ;
		create_word(shell, token, r, (*i));
		token->wrd++;
		r = 0;
	}
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
			|| (shell->input[i] == PIPE))
			setup_index(shell, token, &i);
		else
			i++;
	}
	token->index[token->wrd] = NULL;
	print_matrix(token->index);
}
