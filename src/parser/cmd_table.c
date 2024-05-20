/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:44:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/20 18:53:32 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	fill_cmd_table(t_shell *shell, int start, int pipe, int index)
{
	t_table	*table;

	table = &shell->cmd_table[index];
	table->cmd = 0;
	table->pos = pipe;
	if (find_infile(start, shell, table))
		return (1);
	else if (find_cmd(start - 1, shell->tokens, table))
		return (1);
	else if (find_outfile(start, shell, table))
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

int	find_token_pos(t_shell *shell, int start, int index)
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
		if (!fill_cmd_table(shell, i, pipe, index++))
			return (0);
	return (index);
}

int	count_tkn(char *tokens)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (tokens[++i])
		if (tokens[i] != 'P' && tokens[i] != 'S')
			count++;
	return (count);
}

int	init_cmd_table(t_shell *shell)
{
	t_token		*token;
	char		**input_args;
	int			len;
	int			i;
	static int	index;

	len = 0;
	token = shell->tokens;
	input_args = ft_split(token->tokens, 'P');
	i = -1;
	len = count_tkn(token->tokens);
	shell->cmd_table = malloc(sizeof(t_table) * len);
	if (!shell->cmd_table)
		return (0);
	i = -1;
	while (input_args[++i])
		index = find_token_pos(shell, i, index);
	index = 0;
	collect_garbage(shell, 0, input_args);
	print_cmd_table(shell, len);
	return (1);
}
