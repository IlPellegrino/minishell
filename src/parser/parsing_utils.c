/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:27:50 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/10 17:39:32 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_pathname(t_shell *shell, char *str)
{
	int		i;
	char	*pathname;

	i = -1;
	while (shell->path_env[++i])
	{
		if (ft_strchr(str, '/'))
			pathname = ft_strdup(str);
		else
			pathname = ft_strjoin(shell->path_env[i], str);
		if (!access(pathname, X_OK))
			return (pathname);
		free(pathname);
	}
	if (!access(str, X_OK))
		return (ft_strdup(str));
	return (0);
}

int	get_path(t_shell *shell)
{
	char	*path;
	char	*temp;
	int		i;

	i = -1;
	path = ft_getenv("PATH", shell);
	shell->path_env = ft_split(path, ':');
	if (!shell->path_env)
		return (0);
	free(path);
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

int	is_redir(int c)
{
	if (c == 'H')
		return (1);
	else if (c == 'I')
		return (1);
	if (c == 'O')
		return (1);
	else if (c == 'A')
		return (1);
	return (0);
}

char	*remove_redir(t_token *token)
{
	int		i;
	char	*temp_token;

	temp_token = ft_strdup(token->tokens);
	i = -1;
	while (token->tokens[++i])
		if (is_redir(token->tokens[i]) || is_redir(token->tokens[i - 1]))
			temp_token[i] = 'X';
	return (temp_token);
}
