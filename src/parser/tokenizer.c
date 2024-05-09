/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:59:01 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/09 12:47:47 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_token(t_shell *shell, int find)
{
	int		i;
	t_token *token;

	token = shell->tokens;
	i = -1;
	while (token->tokens[++i])
		if (token->tokens[i] == find)
		{
			token->tokens[i] = 'X';
			return (1);
		}
	return (0);
}

int	priority_execution(t_shell *shell)
{
	t_token	*token;
	int		i;
	int		j;
	char	*new_tokens;

	token = shell->tokens;
	new_tokens = ft_calloc(sizeof(char*), ft_strlen(token->tokens) + 1);
	j = 0;
	shell->n_pipes = 0;
	i = -1;
	while (token->tokens[++i])
		if (token->tokens[i] == '|')
			shell->n_pipes++;
	i = -1;
	if (!shell->n_pipes)
	{
		while (token->tokens[++i])
		{
			if (find_token(shell, 'H'))
				new_tokens[j++] = 'H';
			else if (find_token(shell, 'I'))
				new_tokens[j++] = 'I';
		}
		i = -1;
		while (token->tokens[++i])
			if (token->tokens[i] != 'X')
				new_tokens[j++] = token->tokens[i];
	}
	token->tokens = new_tokens;
	return (1);
}

int	tokenizer(t_shell *shell)
{
	t_token *token;
	int		i;
	
	i = -1;
	token = shell->tokens;
	//print_matrix(token->index);
	token->tokens = ft_calloc(sizeof(char *), matrix_len(token->index) + 1);
	//printf("token->index [%s]\n", token->index[0]);
	while (token->index[++i])
	{
		printf("index = [%s]\n", token->index[i]);
		if (!*token->index[i])
			token->tokens[i] = '/';
		else if (find_cmd(shell, token->index[i]))
			token->tokens[i] = 'C';
		else if (!(ft_strncmp(token->index[i], "<<", 2)))
			token->tokens[i] = 'H';
		else if (!(ft_strncmp(token->index[i], ">>", 2)))
			token->tokens[i] = 'A';
		else if (ft_strchr(token->index[i], '>'))
			token->tokens[i] = 'O';
		else if (ft_strchr(token->index[i], '<'))
			token->tokens[i] = 'I';
		else if (ft_strchr(token->index[i], '|'))
			token->tokens[i] = 'P';
		else
			token->tokens[i] = 'S';
	}
	priority_execution(shell);
	printf("tokens = %s\n", token->tokens);
	return (1);
}