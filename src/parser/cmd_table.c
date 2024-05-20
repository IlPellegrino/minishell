/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:44:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/13 19:29:29 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*find_first(int tkn, t_token *token)
{
	int	i;
	(void)token;

	i = -1;
	while (token->temp_token[++i])
		if (token->temp_token[i] == tkn)
		{
			return (token->index[i]);
		}
	return (0);
}

int	insert_cmd(t_shell *shell, t_cmd *cmd, int tkn, char *input_args)
{
	(void)shell;
	(void)cmd;
	(void)tkn;
	(void)input_args;
	return (1);
}

int	insert_table(t_shell *shell, t_cmd *cmd, int tkn, char *input_args)
{
	t_token *token;
	int		i;
	
	token = shell->tokens;
	if (tkn == 'C')
		return (insert_cmd(shell, cmd, tkn, input_args));
	i = -1;
	while (input_args[++i])
	{
		if (input_args[i] == tkn)
			cmd->command = find_first(tkn, token);
	}
	return (1);
}

int	find_type(t_token *token, int type)
{
	int	i;

	i = -1;
	if (type == ALL_TYPES)
	{
		while (token->tokens[++i] == 'X')
			;
		if (!token->tokens[i])
			return (-1);
		return (i);
	}
	while (token->tokens[++i])
		if (token->tokens[i] == type)
			return (i);
	return (-1);
}

int	fill_cmd_table(t_shell *shell, int len, char **input_args)
{
	int		i;
	t_token *token;
	int		j;
	int		index;

	(void)len;
	token = shell->tokens;
	i = -1;
	while (input_args[++i])
	{
		j = -1;
		while (input_args[i][++j])
		{
			index = find_type(token, ALL_TYPES);
			if (find_type(token, 'H'))
				insert_cmd(shell, &shell->cmd_table[i], 'H', input_args[i]); 
			else if (find_type(token, 'I') >= 0)
				insert_cmd(shell, &shell->cmd_table[i], 'I', input_args[i]);
			else if (find_type(token, 'C') >= 0) 
				insert_cmd(shell, &shell->cmd_table[i], 'C', input_args[i]);
			else
				insert_cmd(shell, &shell->cmd_table[i], token->tokens[j], input_args[i]);
		}
	}
	return (1);
}

int	init_cmd_table(t_shell *shell)
{
	t_token *token;
	char	**input_args;
	int		len;
	t_cmd	cmd;

	(void)cmd;
	token = shell->tokens;
	token->temp_token = ft_strdup(token->tokens);
	len = count_redir(token->tokens) + count_pipes(shell, token->tokens);
	input_args = ft_split(token->tokens, 'P');
	collect_garbage(shell, 0, input_args);
	fill_cmd_table(shell, len, input_args);
	return (1);
}
