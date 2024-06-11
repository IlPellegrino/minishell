/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:45:16 by nromito           #+#    #+#             */
/*   Updated: 2024/06/09 12:24:53 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	write_word(t_shell *shell, t_token *token, int r, int i)
{
	while (++token->start < i)
	{
		if (shell->input[token->start] == DQ)
			copy_in_quotes(shell, token, &r, DQ);
		else if (shell->input[token->start] == SQ)
			copy_in_quotes(shell, token, &r, SQ);
		else if (shell->input[token->start])
			token->index[token->wrd][r++] = shell->input[token->start];
	}
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
	token->flag = check_flag(token);
	token->wrd++;
}

void	copy_in_quotes(t_shell *shell, t_token *token, int (*r), int quote)
{
	if (quote == DQ)
	{
		if (check_word(shell, token, DQ))
			return ;
		token->index[token->wrd][(*r)++] = shell->input[token->start - 1];
		while (shell->input[token->start] && shell->input[token->start] != DQ)
			token->index[token->wrd][(*r)++] = shell->input[token->start++];
		token->index[token->wrd][(*r)++] = shell->input[token->start];
	}
	else if (quote == SQ)
	{
		if (check_word(shell, token, SQ))
			return ;
		token->index[token->wrd][(*r)++] = shell->input[token->start - 1];
		while (shell->input[token->start] && shell->input[token->start] != SQ)
			token->index[token->wrd][(*r)++] = shell->input[token->start++];
		token->index[token->wrd][(*r)++] = shell->input[token->start];
	}
}
