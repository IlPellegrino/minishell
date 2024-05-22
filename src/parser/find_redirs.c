/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:09:43 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/22 15:13:50 by ciusca           ###   ########.fr       */
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

int	fill_cmd(t_shell *shell, t_table table, int i)
{
	t_token *tkn;

	tkn = shell->tokens;
	table.cmd = malloc(sizeof(t_cmd));
	//collect_garbage(shell, table->cmd, 0);
	table.command = tkn->index[i];
	//collect_garbage(shell, 0, table->cmd->cmd_arg);
	table.cmd->pathname = 0;
	tkn->tokens[i] = 'X';
	return (1);
}


int	find_infile(int i, t_shell *shell)
{
	t_token	*token;
	t_table *table;
	char	*temp_space;

	table = &shell->cmd_table[shell->index];
	token = shell->tokens;
	while (token->tokens[i] && token->tokens[i] != 'P')
	{
		if (token->tokens[i] == 'I' || token->tokens[i] == 'H')
		{
			temp_space = ft_strjoin(token->index[i], " ");
			table->command = ft_strjoin(temp_space, token->index[i + 1]);
			free(temp_space);
			collect_garbage(shell, table->command, 0);
			token->tokens[i] = 'X';
			token->tokens[i + 1] = 'X';
			table->cmd = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

int	find_outfile(int start, t_shell *shell)
{
	t_token	*token;
	int		i;
	t_table *table;
	char	*temp_space;

	table = &shell->cmd_table[shell->index];
	i = start;
	token = shell->tokens;
	while (token->tokens[i] && token->tokens[i] != 'P')
	{
		if (token->tokens[i] == 'O' || token->tokens[i] == 'A')
		{
			temp_space = ft_strjoin(token->index[i], " ");
			table->command = ft_strjoin(temp_space, token->index[i + 1]);
			free(temp_space);
			collect_garbage(shell, table->command, 0);
			token->tokens[i] = 'X';
			token->tokens[i + 1] = 'X';
			table->cmd = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

int	find_cmd(t_shell *shell, int i, t_token *tkn)
{
	int		found;
	int		j;
	t_table	*table;
	
	table = &shell->cmd_table[shell->index];
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
			collect_garbage(shell, 0, table->cmd->cmd_arg);
			table->cmd->cmd_arg[j++] = ft_strdup(tkn->index[i]);
			table->cmd->pathname = 0;
			tkn->tokens[i] = 'X';
		}
		else if (tkn->tokens[i] == 'S'
			&& found && !is_redir(tkn->tokens[i - 1]))
		{
			table->cmd->cmd_arg[j++] = ft_strdup(tkn->index[i]);
			tkn->tokens[i] = 'X';
		}
	}
	return (j);
}
