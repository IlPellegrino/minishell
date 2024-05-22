/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:44:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/22 15:50:24 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	fill_cmd_table(t_shell *shell, int start, int pipe)
{
	shell->cmd_table[shell->index].cmd = 0;
	shell->cmd_table[shell->index].pos = pipe;
	if (find_infile(start, shell))
		return (1);
	else if (find_cmd(shell, start - 1, shell->tokens))
		return (1);
	else if (find_outfile(start, shell))
		return (1);
	return (0);
}

int	check_x(char *tokens, int start)
{
	while (tokens[start] == 'X')
		start++;
	if (!tokens[start] || tokens[start] == 'P')
		return (0);
	return (1);
}

int	find_token_pos(t_shell *shell, int start)
{
	int		i;
	int		pipe;
	t_token	*token;

	token = shell->tokens;
	pipe = 0;
	i = -1;
	while (token->tokens[++i] && pipe != start)
		if (token->tokens[i] == 'P')
			pipe++;
	while (check_x(shell->tokens->tokens, i))
	{
		if (!fill_cmd_table(shell, i, pipe))
			return (0);
		shell->index++;
	}
	return (1);
}

int	count_tkn(char *tokens)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	printf("tokens = %s\n", tokens);
	while (tokens[++i])
	{
		if (tokens[i] != 'P' && tokens[i] != 'S')
			count++;
	}
	return (count);
}

int	init_cmd_table(t_shell *shell)
{
	t_token		*token;
	char		**input_args;
	int			i;

	shell->index = 0;
	shell->len = 0;
	token = shell->tokens;
	input_args = ft_split(token->tokens, 'P');
	shell->len = count_tkn(token->tokens);
	shell->cmd_table = malloc(sizeof(t_table) * shell->len);
	if (!shell->cmd_table)
		return (0);
	i = -1;
	while (input_args[++i])
		find_token_pos(shell, i);
	shell->index = 0;
	collect_garbage(shell, 0, input_args);
	print_cmd_table(shell, shell->len);
	return (1);
}
