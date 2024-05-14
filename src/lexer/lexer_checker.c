/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brulutaj <brulutaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:46:29 by nromito           #+#    #+#             */
/*   Updated: 2024/05/14 11:59:58 by brulutaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_quotes(t_shell *shell, int i, int *words)
{
	if (shell->input[i] == DQ)
	{
		while (shell->input[++i] != DQ && shell->input[i])
			;
		if (shell->input[i] == '\0')
			close_shell(shell);
		if (shell->input[++i] == '\0' || shell->input[i] == PIPE)
		{
			(*words)++;
			return (i);
		}
	}
	else if (shell->input[i] == SQ)
	{
		while (shell->input[++i] != SQ && shell->input[i])
			;
		if (shell->input[i] == '\0')
			close_shell(shell);
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
		else if (shell->input[i] == '>')
		{
			while (shell->input[i] == '>')
				i++;
			words++;
		}
		else if (shell->input[i] == '<')
		{
			while (shell->input[i] == '<')
				i++;
			words++;
		}
		else if (shell->input[++i] == '\0' || shell->input[i] == PIPE || shell->input[i] == '>' || shell->input[i] == '<')
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
		close_shell(shell);
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
		close_shell(shell);
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

void	copy_in_quotes(t_shell *shell, t_token *token, int (*r), int quote)
{
	if (quote == DQ)
	{
		if (check_word(shell, token, DQ))
			return ;
		while (shell->input[token->start] != DQ)
			token->index[token->wrd][(*r)++] = shell->input[token->start++];
	}
	else if (quote == SQ)
	{
		if (check_word(shell, token, SQ))
			return ;
		while (shell->input[token->start] != SQ)
			token->index[token->wrd][(*r)++] = shell->input[token->start++];
	}
}

void	create_word(t_shell *shell, t_token *token, int r, int i)
{
	while (++token->start < i)
	{
		if (shell->input[token->start] == DQ)
			copy_in_quotes(shell, token, &r, DQ);
		else if (shell->input[token->start] == SQ)
			copy_in_quotes(shell, token, &r, SQ);
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

void	create_minor(t_shell *shell, t_token *token, int (*i))
{
	int	r;
	int	redir_nbr;

	r = 0;
	redir_nbr = 0;
	while (shell->input[(*i)] == '<')
	{
		redir_nbr++;
		(*i)++;
	}
	printf("entra\n");
	token->index[token->wrd] = ft_calloc(sizeof (char*), redir_nbr + 1);
	if (!token->index[token->wrd])
		return ;
	while (redir_nbr-- > 0)
		token->index[token->wrd][r++] = '<';
	token->wrd++;
}

void	create_major(t_shell *shell, t_token *token, int (*i))
{
	int	r;
	int	redir_nbr;

	r = 0;
	redir_nbr = 0;
	while (shell->input[(*i)] == '>')
	{
		redir_nbr++;
		(*i)++;
	}
	printf("entra\n");
	token->index[token->wrd] = ft_calloc(sizeof (char*), redir_nbr + 1);
	if (!token->index[token->wrd])
		return ;
	while (redir_nbr-- > 0)
		token->index[token->wrd][r++] = '>';
	token->wrd++;
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
	token->index[token->wrd] = ft_calloc(sizeof (char*), pipe_nbr + 1);
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
	if ((shell->input[(*i) - 1] != SPACE && shell->input[(*i)] == PIPE && (*i) != 0)
			|| (shell->input[(*i) - 1] != '>' && shell->input[(*i)] == '>' && (*i) != 0)
			|| (shell->input[(*i) - 1] != '<' && shell->input[(*i)] == '<' && (*i) != 0)
			|| (shell->input[(*i)] != PIPE && shell->input[(*i)] != '>' && shell->input[(*i)] != '<'))
	{
		token->index[token->wrd]
			= ft_calloc(sizeof(char*), (*i) - token->start);
		if (!token->index[token->wrd])
			return ;
		printf("check\n");
		create_word(shell, token, r, (*i));
		token->wrd++;
		r = 0;
	}
	if (shell->input[(*i)] == '<')
		create_minor(shell, token, &(*i));
	if (shell->input[(*i)] == '>')
		create_major(shell, token, &(*i));
	if (shell->input[(*i)] == PIPE)
		create_pipe(shell, token, &(*i));
	if (shell->input[(*i)] == SPACE)
		while (shell->input[(*i)] == SPACE && shell->input[(*i)] != '\0')
			(*i)++;
	printf("i = %d\n", (*i));
	if (shell->input[(*i)] != '\0')
		token->start = (*i) - 1;
}

void	checker(t_shell *shell, t_token *token, int words)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	token->expand = 0;
	token->wrd = 0;
	while (shell->input[i] == 32)
		i++;
	token->start = i - 1;
	while (token->wrd < words)
	{
		if (shell->input[i] == SQ || shell->input[i] == DQ)
			i = quotes_reader(shell, i, &k);
		else if ((shell->input[i] == SPACE) || (shell->input[i] == '\0')
			|| (shell->input[i] == PIPE) || (shell->input[i] == '>') || (shell->input[i] == '<'))
			setup_index(shell, token, &i);
		else
			i++;
	}
	token->index[token->wrd] = NULL;
	print_matrix(token->index);
}
