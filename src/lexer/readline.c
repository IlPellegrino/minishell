/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:55 by nromito           #+#    #+#             */
/*   Updated: 2024/04/30 12:24:37 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	tokenizer(char *tokens)
{
	printf("tokens:\n");
	for (int i = 0; tokens[i]; i++)
		printf("%c ", tokens[i]);
	printf("\n");
}

int	find_cmd(t_shell *shell, char *cmd)
{
	int		i;
	char	*temp_cmd;

	i = -1;
	while (shell->path_env[++i])
	{
		temp_cmd = ft_strjoin(shell->path_env[i], cmd);
		if (!(access(temp_cmd, X_OK)))
			return (1);
	}
	return (0);
}

char *lexer(t_shell *shell)
{
	char 	*tokens;
	int		i;

	tokens = ft_calloc(sizeof(char *), 10);
	i = -1;
	while (shell->mat_input[++i])
	{
		if (find_cmd(shell, shell->mat_input[i]))
			tokens[i] = 'C';
		else
			tokens[i] = 'S';
	}
	tokenizer(tokens);
	return (0);
}
