/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:54:36 by nromito           #+#    #+#             */
/*   Updated: 2024/05/23 15:09:59 by ciusca           ###   ########.fr       */
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

int	parse_first_command(t_shell *shell)
{
	t_token	*token;
	char	*temp_token;
	int		i;

	token = shell->tokens;
	temp_token = ft_strdup(token->tokens);
	i = -1;
	while (temp_token[++i])
	{
		if (is_redir(temp_token[i]))
		{
			temp_token[i] = 'X';
			if (temp_token [i + 1])
				temp_token[i + 1] = 'X';
		}
		else if (temp_token[i] == 'P')
			temp_token[i] = 'X';
	}
	i = 0;
	while (temp_token[i] == 'X')
		i++;
	if (temp_token[i] != 'C' && temp_token[i])
		return (free(temp_token), ft_error(shell, COMMAND, token->index[i]));
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
				return (ft_error(shell, SYNTAX, "\\n"));
		}
		else if (token->tokens[i] == 'P' && token->tokens[i + 1] == 'P')
			return (ft_error(shell, SYNTAX, token->index[i + 1]));
	}
	if (!parse_redirs(shell))
		return (0);
	if (!parse_first_command(shell))
		return (0);
	return (1);
}

int	parsing(t_shell *shell)
{
	if (!tokenizer(shell))
		return (0);
	if (!parse_input(shell))
		return (0);
	if (!init_cmd_table(shell))
		return (0);
	return (1);
}
