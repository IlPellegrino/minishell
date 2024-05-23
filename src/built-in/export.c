/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:40:46 by nromito           #+#    #+#             */
/*   Updated: 2024/05/23 12:53:28 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_setenv()
{
	return (0);
}

int	ft_getenv()
{
	return (0);
}

int	ft_export(char **export_mat)
{
	char	**env_copy;

	if (export_mat)
	{
		env_copy = NULL;
		*env_copy = getenv("NULL");
		return (0);
	}
	return (1);
}