/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:54:36 by nromito           #+#    #+#             */
/*   Updated: 2024/06/11 15:46:55 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	parse_pipe(t_shell *shell)
{
	t_token	*token;
	int		i;

	token = shell->tokens;
	i = -1;
	while (token->tokens[++i])
	{
		if (token->tokens[i] == 'P')
		{
			if (i == 0)
				return (ft_error(shell, SYNTAX, token->index[i]));
			else if (!token->tokens[i + 1])
				return (ft_error(shell, SYNTAX, "\\n"));
		}
	}
	return (1);
}

char	*set_x(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_redir(str[i]))
		{
			str[i] = 'X';
			str[i + 1] = 'X';
		}
	}
	return (str);
}

int	split_pipes(t_shell *shell)
{
	t_token	*token;
	char	*temp_token;
	int		i;
	int		found;

	found = 0;
	token = shell->tokens;
	temp_token = ft_strdup(token->tokens);
	i = -1;
	temp_token = set_x(temp_token);
	i = -1;
	while (temp_token[++i])
	{
		if (temp_token[i] == 'C')
			found = 1;
		if (temp_token[i] == 'P')
			found = 0;
		if (temp_token[i] == 'S' && !found)
		{
			free(temp_token);
			return (ft_error(shell, COMMAND, token->index[i]));
		}
	}
	free(temp_token);
	return (1);
}

int	parse_input(t_shell *shell)
{
	t_token	*token;
	int		i;

	token = shell->tokens;
	i = -1;
	if (!parse_pipe(shell))
		return (0);
	while (token->tokens[++i])
	{
		if (is_redir(token->tokens[i]))
		{
			if (token->tokens[i + 1] == 'P')
				return (ft_error(shell, SYNTAX, token->index[i + 1]));
			else if (!token->tokens[i + 1])
				return (ft_error(shell, SYNTAX, "newline"));
			else if (is_redir(token->tokens[i + 1]))
				return (ft_error(shell, SYNTAX, token->index[i + 1]));
		}
		else if (token->tokens[i] == 'P' && token->tokens[i + 1] == 'P')
			return (ft_error(shell, SYNTAX, token->index[i + 1]));
	}
	if (!parse_redirs(shell))
		return (0);
	return (split_pipes(shell));
}

int	parsing(t_shell *shell)
{
	shell->len = 0;
	if (!tokenizer(shell))
		return (0);
	if (!parse_input(shell))
		return (0);
	if (!init_cmd_table(shell))
		return (0);
	return (1);
}
