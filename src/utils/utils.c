/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:59:43 by nromito           #+#    #+#             */
/*   Updated: 2024/05/06 15:18:46 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	garbage_collector(t_shell *shell)
{
	t_garbage	*garbage;
	
	garbage = shell->collector;
	while (garbage)
	{
		if (garbage->flag == 0)
			free(garbage->arg);
		else if (garbage->flag == 1)
			free_matrix(garbage->arg);
		garbage = garbage->next;
	}
}