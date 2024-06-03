/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:42:41 by nromito           #+#    #+#             */
/*   Updated: 2024/06/02 20:15:27 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

unsigned int	ft_atoi_mod(const char *str)
{
	int	i;
	unsigned int	number;
	unsigned int	neg;

	neg = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n'
		|| str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i ++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] <= '9' && str[i] >= '0')
		number = number * 10 + (str[i++] - 48);
	return (number * neg);
}

void	two_args(char **exit_mat, t_shell *shell)
{
	int	i;

	i = -1;
	while (exit_mat[1][++i])
		if (!ft_isdigit(exit_mat[1][i]) && exit_mat[1][0] != '-')
			break;
	if (!exit_mat[1][i])
	{
		shell->error = (ft_atoi_mod(exit_mat[1]) % 256);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		if (ft_atoi_mod(exit_mat[1]) != 256
			&& ft_atoi_mod(exit_mat[1]) % 256 == 0)
			printf("minishell: exit: %s: numeric argument required\n", exit_mat[1]);
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

void	more_args(char **exit_mat, t_shell *shell)
{
	int	first;
	int	i;

	i = -1;
	first = 0;
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
	else
	{
		shell->error = 1;
		printf("minishell: exit: too many arguments\n");
	}
}

void	ft_exit(char **exit_mat, t_shell *shell)
{
	if (matrix_len(exit_mat) < 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		close_shell(shell);
	}
	else if (matrix_len(exit_mat) < 3)
		two_args(exit_mat, shell);
	else if (matrix_len(exit_mat) > 2)
		more_args(exit_mat, shell);
}
