/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:44:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/13 13:15:19 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	fill_redirs(int end, t_token *token, t_table *table)
{
	int	count;
	int	j;
	int	fd_pos;

	table->token = (t_token *)token;
	fd_pos = 0;
	j = 0;
	table->redirs = 0;
	count = count_redirects(token, end);
	if (count)
	{
		table->redirs = ft_calloc(sizeof(char *), count + 1);
		if (!table->redirs)
			return (0);
		table->fd = malloc(sizeof(int) * count);
		j = find_infile(table, token, end, &fd_pos);
		find_outfile(table, &fd_pos, end, j);
	}
	return (0);
}

char	**get_args(t_token *token, int end)
{
	int		i;
	int		count;
	char	**cmd_arg;
	int		j;

	j = 0;
	i = -1;
	count = 0;
	while (++i < end)
		if (token->tokens[i] == 'C' || token->tokens[i] == 'S')
			count++;
	cmd_arg = ft_calloc(sizeof(char *), count + 1);
	if (!cmd_arg)
		return (0);
	i = -1;
	while (++i < end)
	{
		if (token->tokens[i] != 'X')
		{
			cmd_arg[j++] = ft_strdup(token->index[i]);
			token->tokens[i] = 'X';
		}
	}
	return (cmd_arg);
}

int	fill_cmd(t_shell *shell, t_token *token, t_table *table, int end)
{
	int		i;
	t_cmd	*cmd;

	table->command = 0;
	cmd = NULL;
	if (is_cmd(token, end))
	{
		i = -1;
		while (++i < end)
		{
			if (token->tokens[i] != 'X')
			{
				table->command = token->index[i];
				break;
			}
		}
		cmd = malloc(sizeof(t_cmd));
		cmd->cmd_arg = 0;
		cmd->cmd_arg = get_args(token, end);
		cmd->pathname = get_pathname(shell, table->command);
	}
	table->cmd = cmd;
	return (1);
}

int	fill_cmd_table(t_shell *shell, t_table *table, t_token *token, int end)
{
	int	count;

	count = count_redirects(token, end);
	table->redirs = 0;
	if (count)
		fill_redirs(end, token, table);
	fill_cmd(shell, token, table, end);
	return (1);
}

int	init_cmd_table(t_shell *shell)
{
	t_token		*token;
	t_table		*table;
	int			i;
	int			j;

	j = 0;
	i = -1;
	token = shell->tokens;
	shell->len = count_pipes(token->tokens);
	table = malloc(sizeof(t_table) * shell->len);
	shell->cmd_table = table;
	table->cmd = 0;
	while (token->tokens[++i])
	{
		if (token->tokens[i] == 'P')
		{
			token->tokens[i] = 'X';
			fill_cmd_table(shell, &table[j++], token, i);
		}
	}
	fill_cmd_table(shell, &table[j++], token, i);
	token->redirs = 0;
	return (1);
}
