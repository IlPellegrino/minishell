/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:55 by nromito           #+#    #+#             */
/*   Updated: 2024/05/22 11:54:00 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_cmd_path(t_shell *shell, char *cmd)
{
	int		i;

	i = -1;
	while (shell->path_env[++i])
	{
		shell->cmd_name = ft_strjoin(shell->path_env[i], cmd);
		collect_garbage(shell, shell->cmd_name, 0);
		if (access_p(shell->cmd_name, X_OK) == 0)
			return (1);
	}
	return (0);
}

int		lexer(t_shell *shell)
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
