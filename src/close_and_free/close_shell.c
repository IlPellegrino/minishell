/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:32:57 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/10 17:15:57 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_cmd(t_table *table)
{
	if (table->cmd->cmd_arg)
	{
		free_matrix(table->cmd->cmd_arg);
		table->cmd->cmd_arg = 0;
	}
	if (table->cmd->pathname)
	{
		free(table->cmd->pathname);
		table->cmd->pathname = 0;
	}
	free(table->cmd);
	table->cmd = 0;
}

void	free_cmd_table(t_shell *shell)
{
	t_table	*table;
	int		i;

	i = -1;
	if (shell->len)
	{
		while (++i < shell->len)
		{
			table = &shell->cmd_table[i];
			if (table->redirs)
			{
				free_matrix(table->redirs);
				table->redirs = 0;
				free(table->fd);
			}
			if (table->cmd)
				free_cmd(table);
		}
	}
	free(shell->cmd_table);
	shell->cmd_table = 0;
}

t_garbage	*new_node(char *arg, char **mat)
{
	t_garbage	*node;

	node = malloc(sizeof(t_garbage));
	if (!node)
		return (0);
	node->arg = arg;
	node->mat = mat;
	node->next = NULL;
	return (node);
}

int	collect_garbage(t_shell *shell, char *arg, char **mat)
{
	t_garbage	*collect;

	collect = shell->collector;
	while (collect->next)
		collect = collect->next;
	collect->next = new_node(arg, mat);
	return (1);
}

void	close_shell(t_shell *shell)
{
	t_garbage	*garbage;
	t_garbage	*temp;

	garbage = shell->collector;
	temp = garbage->next;
	free(shell->tokens);
	free(garbage);
	garbage = NULL;
	garbage = temp;
	while (garbage)
	{
		if (garbage->arg)
			free(garbage->arg);
		if (garbage->mat)
			free_matrix(garbage->mat);
		temp = garbage->next;
		free(garbage);
		garbage = temp;
	}
	if (shell->cmd_table)
		free_cmd_table(shell);
	exit(shell->error);
}
