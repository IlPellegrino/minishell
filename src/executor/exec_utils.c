/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:59:18 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/04 11:51:31 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_builtin(char *str)
{
	int		cmd_len;

	cmd_len = ft_strlen(str);
	if (!(ft_strncmp(str, "echo", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "cd", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "pwd", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "export", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "unset", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "env", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "exit", cmd_len)))
		return (1);
	return (0);
}

