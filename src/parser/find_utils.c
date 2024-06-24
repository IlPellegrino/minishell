/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:10:12 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/24 18:01:40 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	count_redirects(t_token *token, int end)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < end)
	{
		if (is_redir(token->tokens[i]))
		{
			count++;
		}
	}
	return (count);
}

int	count_pipes(char *str)
{
	int	i;
	int	count;

	count = 1;
	i = -1;
	while (str[++i])
		if (str[i] == 'P')
			count++;
	return (count);
}

int	is_cmd(t_token *token, int end)
{
	int	i;

	i = -1;
	while (++i < end)
		if (token->tokens[i] == 'C' || token->tokens[i] == 'S')
			return (1);
	return (0);
}

int	find_infile(t_table *table, t_token *token, int end, int *fd_pos)
{
	int		i;
	int		j;
	char	*space;
	char	*redir;

	j = 0;
	i = -1;
	while (++i < end)
	{
		if (token->tokens[i] == 'I' || token->tokens[i] == 'H')
		{
			token->tokens[i] = 'X';
			token->tokens[i + 1] = 'X';
			space = ft_strjoin(token->index[i], " ");
			redir = ft_strjoin(space, token->index[i + 1]);
			free(space);
			table->fd[(*fd_pos)++] = token->redirs[i + 1];
			table->redirs[j++] = redir;
		}
	}
	return (j);
}

int	find_outfile(t_table *table, int *fd_pos, int end, int j)
{
	int		i;
	char	*redir;
	char	*space;
	t_token	*token;

	token = (t_token *)table->token;
	i = -1;
	while (++i < end)
	{
		if (token->tokens[i] == 'O' || token->tokens[i] == 'A')
		{
			token->tokens[i] = 'X';
			token->tokens[i + 1] = 'X';
			space = ft_strjoin(token->index[i], " ");
			redir = ft_strjoin(space, token->index[i + 1]);
			free(space);
			table->fd[(*fd_pos)++] = token->redirs[i + 1];
			table->redirs[j++] = redir;
		}
	}
	return (1);
}
