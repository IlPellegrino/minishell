/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:55 by nromito           #+#    #+#             */
/*   Updated: 2024/05/22 18:00:13 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_builtins(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "exit", len))
		return (1);
	else if (!ft_strncmp(cmd, "unset", len))
		return (1);
	else if (!ft_strncmp(cmd, "export", len))
		return (1);
	else if (!ft_strncmp(cmd, "cd", len))
		return (1);
	return (0);
}

int	find_cmd_path(t_shell *shell, char *cmd)
{
	int		i;

	i = -1;
	if (find_builtins(cmd))
		return (1);
	while (shell->path_env[++i])
	{
		if (!ft_strchr(cmd, '/'))
			shell->cmd_name = ft_strjoin(shell->path_env[i], cmd);
		else
			shell->cmd_name = ft_strdup(cmd);
		collect_garbage(shell, shell->cmd_name, 0);
		if (access_p(shell->cmd_name, X_OK) == 0)
			return (1);
	}
	return (0);
}

int	lexer(t_shell *shell)
{
	int		words;
	t_token	*token;

	token = shell->tokens;
	shell->error = errno;
	words = count_wrds(shell);
	if (words == 0)
		return (0);
	token->flag = 0;
	token->wrd = 0;
	token->index = ft_calloc(sizeof (char *), words + 1);
	if (!token->index)
		return (0);
	collect_garbage(shell, 0, token->index);
	token->flag = ft_calloc(sizeof(char *), words + 1);
	collect_garbage(shell, token->flag, 0);
	checker(shell, token, words);
	printf("flag %s\n", token->flag);
	return (1);
}
