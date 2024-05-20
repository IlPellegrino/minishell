/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:46:29 by nromito           #+#    #+#             */
/*   Updated: 2024/05/20 14:52:41 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// void	flag_for_parser(t_shell *shell, int i)
// {
// 	if (shell->input[i] == '>')
// 		;
// 		//shell->tokens->flag = 1;
// }

int	check_quotes(t_shell *shell, int i, int *words)
{
	if (shell->input[i] == DQ)
	{
		while (shell->input[++i] != DQ && shell->input[i])
			;
		if (shell->input[i] == '\0')
			close_shell(shell);
		if (shell->input[++i] == '\0' || shell->input[i] == PIPE
			|| shell->input[i] == '>' || shell->input[i] == '<')
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
		if (shell->input[++i] == '\0' || shell->input[i] == PIPE
			|| shell->input[i] == '>' || shell->input[i] == '<')
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
	if (shell->input[(*i) - 1] != PIPE && shell->input[(*i) - 1] != '<'
		&& shell->input[(*i) - 1] != '>')
		words++;
	while (shell->input[++(*i)] == SPACE)
		;
	return (words);
}

int	check_redirs(t_shell *shell, int words, int (*i))
{
	if (shell->input[(*i)] == PIPE)
		while (shell->input[(*i)] == PIPE)
			(*i)++;
	else if (shell->input[(*i)] == '>')
		while (shell->input[(*i)] == '>')
			(*i)++;
	else if (shell->input[(*i)] == '<')
		while (shell->input[(*i)] == '<')
			(*i)++;
	return (words + 1);
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
		else if (shell->input[i] == '>' || shell->input[i] == '<'
			|| shell->input[i] == PIPE)
			words = check_redirs(shell, words, &i);
		else if (shell->input[++i] == '\0' || shell->input[i] == PIPE
			|| shell->input[i] == '>' || shell->input[i] == '<')
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

void	write_word(t_shell *shell, t_token *token, int r, int i)
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
	token->index[token->wrd] = ft_calloc(sizeof (char *), redir_nbr + 1);
	if (!token->index[token->wrd])
		return ;
	while (redir_nbr-- > 0)
		token->index[token->wrd][r++] = '<';
	if (!token->flag)
		token->flag = ft_calloc(sizeof (char *), token->wrd + 2);
	token->flag = check_flag(token);
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
	token->index[token->wrd] = ft_calloc(sizeof (char *), redir_nbr + 1);
	if (!token->index[token->wrd])
		return ;
	while (redir_nbr-- > 0)
		token->index[token->wrd][r++] = '>';
	if (!token->flag)
		token->flag = ft_calloc(sizeof (char *), token->wrd + 2);
	token->flag = check_flag(token);
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
	token->index[token->wrd] = ft_calloc(sizeof (char *), pipe_nbr + 1);
	if (!token->index[token->wrd])
		return ;
	while (pipe_nbr-- > 0)
		token->index[token->wrd][r++] = '|';
	if (!token->flag)
		token->flag = ft_calloc(sizeof (char *), token->wrd + 2);
	token->flag = check_flag(token);
	token->wrd++;
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
	if (!token->flag)
		token->flag = ft_calloc(sizeof (char *), token->wrd + 2);
	token->flag = check_flag(token);
	expand_value(shell, token);
	token->index[token->wrd] = remove_quotes(shell, token, count_quotes(token));
	token->wrd++;
}

void	choose_if(t_shell *shell, t_token *token, int (*i))
{
	if (shell->input[(*i)] == PIPE && shell->input[(*i) - 1] != SPACE
		&& shell->input[(*i) - 1] != '>'
		&& (*i) != 0 && shell->input[(*i) - 1] != '<')
		create_word(shell, token, &(*i));
	else if (shell->input[(*i)] == '<' && shell->input[(*i) - 1] != SPACE
		&& shell->input[(*i) - 1] != '>'
		&& (*i) != 0 && shell->input[(*i) - 1] != PIPE)
		create_word(shell, token, &(*i));
	else if (shell->input[(*i)] == '>' && shell->input[(*i) - 1] != SPACE
		&& shell->input[(*i) - 1] != PIPE
		&& (*i) != 0 && shell->input[(*i) - 1] != '<')
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
