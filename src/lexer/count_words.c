/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:40:12 by nromito           #+#    #+#             */
/*   Updated: 2024/06/11 15:51:12 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_quotes(t_shell *shell, int *i, int *words)
{
	if (shell->input[*i] == DQ)
	{
		while (shell->input[++*i] != DQ && shell->input[*i])
			;
		if (shell->input[*i] == '\0')
			return (0);
		if (shell->input[++*i] == '\0' || shell->input[*i] == PIPE
			|| shell->input[*i] == '>' || shell->input[*i] == '<')
			(*words)++;
	}
	else if (shell->input[*i] == SQ)
	{
		while (shell->input[++*i] != SQ && shell->input[*i])
			;
		if (shell->input[*i] == '\0')
			return (0);
		if (shell->input[++*i] == '\0' || shell->input[*i] == PIPE
			|| shell->input[*i] == '>' || shell->input[*i] == '<')
			(*words)++;
	}
	return (1);
}

int	pipe_checker(t_shell *shell, int i, int *words)
{
	if (shell->input[i + 1] != SPACE && shell->input[i - 1] != SPACE
		&& shell->input[i + 1] != TAB && shell->input[i - 1] != TAB)
		(*words)++;
	return (++i);
}

int	check_space(t_shell *shell, int words, int (*i))
{
	if (shell->input[(*i) - 1] != PIPE && shell->input[(*i) - 1] != '<'
		&& shell->input[(*i) - 1] != '>')
		words++;
	while (shell->input[++(*i)] == SPACE || shell->input[*i] == TAB)
		;
	return (words);
}

int	check_redirs(t_shell *shell, int words, int (*i))
{
	if (shell->input[(*i)] == PIPE)
		while (shell->input[(*i)] == PIPE)
			(*i)++;
	else if (shell->input[(*i)] == '>')
		while (shell->input[(*i)] == '>')
			(*i)++;
	else if (shell->input[(*i)] == '<')
		while (shell->input[(*i)] == '<')
			(*i)++;
	return (words + 1);
}

int	count_wrds(t_shell *shell)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (shell->input[i] == SPACE || shell->input[i] == TAB)
		i++;
	while (shell->input[i] != '\0')
	{
		if (shell->input[i] == DQ || shell->input[i] == SQ)
		{
			if (!check_quotes(shell, &i, &words))
				return (0);
		}
		else if (shell->input[i] == SPACE || shell->input[i] == TAB)
			words = check_space(shell, words, &i);
		else if (shell->input[i] == '>' || shell->input[i] == '<'
			|| shell->input[i] == PIPE)
			words = check_redirs(shell, words, &i);
		else if (shell->input[++i] == '\0' || shell->input[i] == PIPE
			|| shell->input[i] == '>' || shell->input[i] == '<')
			words++;
	}
	return (words);
}
