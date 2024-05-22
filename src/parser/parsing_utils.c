/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:27:50 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/22 15:16:46 by ciusca           ###   ########.fr       */
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

void	print_cmd_table(t_shell *shell, int len)
{
	t_table	table;
	int		i;
	int		j;

	i = -1;
	printf("len %d\n", len);
	while (++i < len)
	{
		table = shell->cmd_table[i];
		j = 0;
		printf("element = %s\n", table.command);
		if (table.cmd)
			while (table.cmd->cmd_arg[++j])
				printf("[%d] args ---> %s\n", j, table.cmd->cmd_arg[j]);
	}
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
