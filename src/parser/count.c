/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:09:43 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/13 17:10:07 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	count_pipes(t_shell *shell, char *tokens)
{
	int		i;

	shell->n_pipes = 0;
	i = -1;
	while (tokens[++i])
		if (tokens == 'P')
			shell->n_pipes++;
	return (shell->n_pipes + 1);
}

int	count_redir(char *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (is_redir(tokens[i]))
		{
			i++;
			count++;
		}
		i++;
	}
	return (count);
}