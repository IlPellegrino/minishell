/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:54:36 by nromito           #+#    #+#             */
/*   Updated: 2024/05/20 19:09:00 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_path(t_shell *shell)
{
	char	*path;
	char	*temp;
	int		i;

	i = -1;
	path = getenv("PATH");
	shell->path_env = ft_split(path, ':');
	if (!shell->path_env)
		return (0);
	while (shell->path_env[++i])
	{
		temp = ft_strdup(shell->path_env[i]);
		free(shell->path_env[i]);
		shell->path_env[i] = ft_strjoin(temp, "/");
		free(temp);
	}
	collect_garbage(shell, 0, shell->path_env);
	return (1);
}

int	parse_command(t_shell *shell)
{
	t_token	*token;
	int		i;

	token = shell->tokens;
	token->temp_token = remove_redir(token);
	collect_garbage(shell, token->temp_token, 0);
	i = -1;
	while (token->temp_token[i] == 'X')
		i++;
	if (token->temp_token[i] != 'C' && token->temp_token[i])
		return (ft_error(COMMAND, token->index[i]));
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
			temp_token[i + 1] = 'X';
		}
		else if (temp_token[i] == 'P')
			temp_token[i] = 'X';
	}
	i = 0;
	while (temp_token[i] == 'X')
		i++;
	if (temp_token[i] != 'C' && temp_token[i])
		return (ft_error(COMMAND, token->index[i]));
	return (1);
}

int	parse_input(t_shell *shell)
{
	t_token	*token;
	int		i;

	token = shell->tokens;
	i = -1;
	if (!parse_first_command(shell))
		return (0);
	while (token->tokens[++i])
	{
		if (is_redir(token->tokens[i]))
		{
			if (token->tokens[i + 1] == 'P')
				return (ft_error(SYNTAX, token->index[i + 1]));
			else if (!token->tokens[i + 1])
				return (ft_error(SYNTAX, "\\n"));
		}
		else if (token->tokens[i] == 'P' && token->tokens[i + 1] == 'P')
			return (ft_error(SYNTAX, token->index[i + 1]));
	}
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
