/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:43:26 by nromito           #+#    #+#             */
/*   Updated: 2024/07/03 12:24:58 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (0);
	printf("%s\n", path);
	free(path);
	return (1);
}
