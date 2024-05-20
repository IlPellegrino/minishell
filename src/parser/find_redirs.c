/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:09:43 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/20 16:49:46 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	count_command_args(t_token *token, int start)
{
	int	count;

	count = 0;
	while (token->tokens[start] && token->tokens[start] != 'P')
	{
		if (token->tokens[start] == 'C' || token->tokens[start] == 'S')
			count++;
		start++;
	}
	return (count);
}

int	find_infile(int i, t_shell *shell, t_table *table)
{
	t_token *token;

	token = shell->tokens;
	while (token->tokens[i] && token->tokens[i] != 'P')
	{
		if (token->tokens[i] == 'I' || token->tokens[i] == 'H')
		{
			table->command = ft_strjoin(token->index[i], token->index[i + 1]);
			token->tokens[i] = 'X';
			token->tokens[i + 1] = 'X';
			return (1);
		}
		i++;
	}
	return (0);	
}

int	find_outfile(int start, t_shell *shell, t_table *table)
{
	t_token *token;
	int		i;

	i = start;
	token = shell->tokens;
	while (token->tokens[i] && token->tokens[i] != 'P')
	{
		if (token->tokens[i] == 'O' || token->tokens[i] == 'A')
		{
			table->command = ft_strjoin(token->index[i], token->index[i + 1]);
			token->tokens[i] = 'X';
			token->tokens[i + 1] = 'X';
			return (1);
		}
		i++;
	}
	return (0);	
}

int	find_cmd(int start, t_shell *shell, t_table *table)
{
	t_token *token;
	int		found;
	int		j;

	j = 0;
	found = 0;
	token = shell->tokens;
	while (token->tokens[start] && token->tokens[start] != 'P')
	{
		if (token->tokens[start] == 'C')
		{
			found = 1;
			table->cmd = malloc(sizeof(t_cmd));
			table->command = token->index[start];
			table->cmd->cmd_arg = ft_calloc(sizeof(char*), count_command_args(token, start) + 1);
			table->cmd->cmd_arg[j++] = token->index[start];
			table->cmd->pathname = 0;
			token->tokens[start] = 'X';
		}
		else if (token->tokens[start] == 'S' && found == 1 && !is_redir(token->tokens[start - 1]))
		{
			table->cmd->cmd_arg[j++] = token->index[start];
			token->tokens[start] = 'X';
		}
		start++;
	}
	return (j);
}

void	print_cmd_table(t_shell *shell, int len)
{
	t_table table;
	int		i;
	int		j;
	
	i = -1;
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

