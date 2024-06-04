/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:09:43 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/31 14:14:37 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	fill_fds(t_token *token, t_table *table)
{
	int		i;
	int		end;
	int		j;

	j = 0;
	i = 0;
	while (token->redirs[i] == -42)
		i++;
	end = matrix_len(table->redirs) + i;
	while (i < end)
	{
		table->fd[j++] = token->redirs[i];
		token->redirs[i] = -42;
		i++;
	}
	return (1);
}
