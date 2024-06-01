/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:42:41 by nromito           #+#    #+#             */
/*   Updated: 2024/06/01 17:48:56 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exit(char **exit_mat, t_shell *shell)
{
	int	i;
	int	j;
	int	flag;
	int	first;

	i = -1;
	j = 0;
	flag = 0;
	first = 0;
	if (matrix_len(exit_mat) < 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		close_shell(shell);
	}
	else if (matrix_len(exit_mat) < 3)
	{
		while (exit_mat[1][++i])
			if (!ft_isdigit(exit_mat[1][i]) && exit_mat[1][0] != '-')
				break;
		if (!exit_mat[1][i])
		{
			shell->error = (ft_atoi(exit_mat[1]) % 256);
			ft_putstr_fd("exit\n", STDERR_FILENO);
			close_shell(shell);
		}
		else
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			printf("minishell: exit: %s: numeric argument required\n", exit_mat[1]);
			shell->error = 2;
			close_shell(shell);
		}
	}
	else if (matrix_len(exit_mat) > 2)
	{
		i = -1;
		while (exit_mat[1][++i])
			if (!ft_isdigit(exit_mat[1][i]) && exit_mat[1][0] != '-')
				first = 1;
		if (first == 1)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			printf("minishell: exit: %s: numeric argument required\n", exit_mat[1]);
			shell->error = 2;
			close_shell(shell);
		}
		else if (!exit_mat[j])
		{
			shell->error = 1;
			printf("minishell: exit: too many arguments\n");
		}
	}
}
