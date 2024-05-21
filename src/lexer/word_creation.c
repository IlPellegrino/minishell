/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:45:16 by nromito           #+#    #+#             */
/*   Updated: 2024/05/21 14:12:14 by nromito          ###   ########.fr       */
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
		else
			if (shell->input[token->start] != '\0')
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
