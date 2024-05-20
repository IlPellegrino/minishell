/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:09:43 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/20 18:49:19 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	n_args(t_token *token, int start)
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
	t_token	*token;

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
	t_token	*token;
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

int	find_cmd(int i, t_token *tkn, t_table *table)
{
	int		found;
	int		j;

	j = 0;
	found = 0;
	while (tkn->tokens[++i] && tkn->tokens[i] != 'P')
	{
		if (tkn->tokens[i] == 'C')
		{
			found = 1;
			table->cmd = malloc(sizeof(t_cmd));
			table->command = tkn->index[i];
			table->cmd->cmd_arg = ft_calloc(sizeof(char *), n_args(tkn, i) + 1);
			table->cmd->cmd_arg[j++] = tkn->index[i];
			table->cmd->pathname = 0;
			tkn->tokens[i] = 'X';
		}
		else if (tkn->tokens[i] == 'S'
			&& found && !is_redir(tkn->tokens[i - 1]))
		{
			table->cmd->cmd_arg[j++] = tkn->index[i];
			tkn->tokens[i] = 'X';
		}
	}
	return (j);
}

void	print_cmd_table(t_shell *shell, int len)
{
	t_table	table;
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
