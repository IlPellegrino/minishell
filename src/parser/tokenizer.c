/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:59:01 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/13 14:38:47 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*int	find_token(t_shell *shell, int find, int pipe)
{
	t_token *token;
	int		i;

	i = 0;
	token = shell->tokens;
	while (token->tokens[i] && token->tokens[i] != 'P')
	{
		if (token->tokens[i] == find)
		{
			token->tokens[i] = 'X';
			return (1);
		}
		i++;
	}
	if (pipe == 1)
	{
		token->tokens[i] = 'X';
		return (1);
	}
	return (0);
}
char	*infile_heredoc_priority(t_shell *shell, char *new_tokens)
{
	t_token *token;
	int		i;
	int		j;

	i = -1;
	j = 0;
	token = shell->tokens;
	while (token->tokens[++i])
	{
		if (find_token(shell, 'H', 0))
			new_tokens[j++] = 'H';
		else if (find_token(shell, 'I', 0))
			new_tokens[j++] = 'I';
		else if (find_token(shell, 'C', 0))
			new_tokens[j++] = 'C';
		else if (find_token(shell, 'S', 0))
			new_tokens[j++] = 'S';
		else if (find_token(shell, 'O', 0))
			new_tokens[j++] = 'O';
		else if (find_token(shell, 'A', 0))
			new_tokens[j++] = 'A';
		else if (find_token(shell, 'P', 1))
			new_tokens[j++] = 'P';
	}
	return (new_tokens);
}


int	prioritize_commands(t_shell *shell)
{
	t_token	*token;
	int		i;
	int		start;
	char	*new_tokens;

	token = shell->tokens;
	new_tokens = ft_calloc(sizeof(char*), ft_strlen(token->tokens) + 1);
	if (!new_tokens)
		return (0);
	start = 0;
	i = -1;
	shell->n_pipes = 0;
	while (token->tokens[++i])
		if (token->tokens[i] == '|')
			shell->n_pipes++;
	i = -1;
	new_tokens = infile_heredoc_priority(shell, new_tokens);
	token->tokens = ft_strdup(new_tokens);
	free(new_tokens);
	return (1);
}*/

int	set_token(t_shell *shell, t_token *token, int *i)
{
	if (!*token->index[*i])
		token->tokens[*i] = '/';
	else if (find_cmd(shell, token->index[*i]))
		token->tokens[*i] = 'C';
	else if (!(ft_strncmp(token->index[*i], "<<", 2)))
		token->tokens[*i] = 'H';
	else if (!(ft_strncmp(token->index[*i], ">>", 2)))
		token->tokens[*i] = 'A';
	else if (token->index[*i][0] == '>')
		token->tokens[*i] = 'O';
	else if (token->index[*i][0] == '<')
		token->tokens[*i] = 'I';
	else if (token->index[*i][0] == '|')
		token->tokens[*i] = 'P';
	else
		token->tokens[*i] = 'S';
	return (1);
}

int	tokenizer(t_shell *shell)
{
	t_token *token;
	int		i;
	
	token = shell->tokens;
	i = -1;
	token->tokens = ft_calloc(sizeof(char *), matrix_len(token->index) + 1);
	if (!token->tokens)
		close_shell(shell);
	collect_garbage(shell, token->tokens, 0);
	while (token->index[++i])
		if (!set_token(shell, token, &i))
			return (0);
	printf("tokens = [%s]\n", token->tokens);
	if (!token->tokens[1])
		printf("len = %zu\n", ft_strlen(token->tokens));
	return (1);
}
