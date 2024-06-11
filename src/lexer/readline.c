/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:55 by nromito           #+#    #+#             */
/*   Updated: 2024/06/09 12:54:12 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_builtins(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "exit", len))
		return (1);
	else if (!ft_strncmp(cmd, "unset", len))
		return (1);
	else if (!ft_strncmp(cmd, "export", len))
		return (1);
	else if (!ft_strncmp(cmd, "cd", len))
		return (1);
	return (0);
}

int	find_cmd_path(t_shell *shell, char *cmd, int pos)
{
	int		i;

	i = -1;
	if (!cmd[0])
		return (0);
	if (find_builtins(cmd))
		return (1);
	if (pos && is_redir(shell->tokens->tokens[pos - 1]))
		return (0);
	while (shell->path_env[++i])
	{
		if (!ft_strchr(cmd, '/'))
			shell->cmd_name = ft_strjoin(shell->path_env[i], cmd);
		else
			shell->cmd_name = ft_strdup(cmd);
		collect_garbage(shell, shell->cmd_name, 0);
		if (access_p(shell->cmd_name, X_OK) == 0)
			return (1);
	}
	return (0);
}

int	lexer(t_shell *shell)
{
	int		words;
	t_token	*token;

	token = shell->tokens;
	words = count_wrds(shell);
	if (words == 0)
		return (0);
	token->flag = 0;
	token->wrd = 0;
	token->index = ft_calloc(sizeof (char *), words + 1);
	if (!token->index)
		return (0);
	collect_garbage(shell, 0, token->index);
	token->flag = ft_calloc(sizeof(char *), words + 1);
	if (!token->flag)
		return (0);
	collect_garbage(shell, token->flag, 0);
	checker(shell, token, words);
	printf("flag %s\n", token->flag);
	return (1);
}

void	checker(t_shell *shell, t_token *token, int words)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	token->wrd = 0;
	while (shell->input[i] == SPACE || shell->input[i] == TAB)
		i++;
	token->start = i - 1;
	while (token->wrd < words)
	{
		if (shell->input[i] == SQ || shell->input[i] == DQ)
			i = quotes_reader(shell, i, &k);
		else if ((shell->input[i] == SPACE) || (shell->input[i] == '\0')
			|| (shell->input[i] == PIPE) || (shell->input[i] == '>')
			|| (shell->input[i] == '<') || shell->input[i] == TAB)
			setup_index(shell, token, &i);
		else
			i++;
	}
	token->index[token->wrd] = NULL;
	print_matrix(token->index);
}

void	setup_index(t_shell *shell, t_token *token, int *i)
{
	if (shell->input[(*i)] == PIPE
		|| shell->input[(*i)] == '>' || shell->input[(*i)] == '<')
		choose_if(shell, token, &(*i));
	else if (shell->input[(*i)] != PIPE
		&& shell->input[(*i)] != '>' && shell->input[(*i)] != '<')
		create_word(shell, token, &(*i));
	if (shell->input[(*i)] == '<')
		create_minor(shell, token, &(*i));
	if (shell->input[(*i)] == '>')
		create_major(shell, token, &(*i));
	if (shell->input[(*i)] == PIPE)
		create_pipe(shell, token, &(*i));
	if (shell->input[(*i)] == SPACE || shell->input[*i] == TAB)
		while (shell->input[(*i)] &&
			(shell->input[(*i)] == SPACE || shell->input[*i] == TAB))
			(*i)++;
	if (shell->input[(*i)])
		token->start = (*i) - 1;
}
