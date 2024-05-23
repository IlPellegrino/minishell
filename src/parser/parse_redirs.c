/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:34:56 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/23 14:54:57 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_redir(t_shell *shell, t_token *token, int i)
{
	int	fd;
	
	fd = -1;
	if (token->tokens[i - 1] == 'I')
		fd = open(token->index[i], O_RDONLY);
	else if (token->tokens[i - 1] == 'A')
		fd = open(token->index[i], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (token->tokens[i - 1] == 'O')
		fd = open(token->index[i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	shell->error = errno;
	if (fd < 0)
		return (ft_error(OPEN_ERR, token->index[i]));
	token->redirs[i] = fd;
	return (1);
}

int	count_redirs(char *tokens)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (tokens[++i])
		if (is_redir(tokens[i]))
			count++;
	return (count);	
}

int	parse_redirs(t_shell *shell)
{
	t_token *token;
	int		n_red;
	int		i;

	token = shell->tokens;
	n_red = count_redirs(token->tokens);
	token->redirs = malloc(sizeof(int) * ft_strlen(token->tokens));
	collect_garbage(shell, (char *)token->redirs, 0);
	i = -1;
	while (++i < (int)ft_strlen(token->tokens))
		token->redirs[i] = -1;
	i = -1;
	while (token->tokens[++i])
	{
		if (token->tokens[i] == 'H')
			;//ft_heredoc;
		else if (is_redir(token->tokens[i]))
		{
			if (!open_redir(shell, token, i + 1))
				return (0);
		}
	}
	return (1);
}
