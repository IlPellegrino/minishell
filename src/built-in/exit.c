/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:42:41 by nromito           #+#    #+#             */
/*   Updated: 2024/06/12 17:05:56 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_atoi_mod(const char *str)
{
	int		i;
	int		number;
	int		neg;

	neg = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n'
		|| str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] <= '9' && str[i] >= '0')
		number = number * 10 + (str[i++] - 48);
	return (number * neg);
}

int	two_args(char **exit_mat, t_shell *shell, pid_t pid)
{
	int	i;

	i = -1;
	while (exit_mat[1][++i])
		if (!ft_isdigit(exit_mat[1][i]) && exit_mat[1][0] != '-')
			break ;
	if (!exit_mat[1][i])
	{
		shell->error = (ft_atoi_mod(exit_mat[1]) % 256);
		if (!pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		if (ft_strlen(exit_mat[1]) >= ft_strlen("9223372036854775807"))
			if (ft_strncmp(exit_mat[1], "9223372036854775807",
					ft_strlen("9223372036854775807")) > 0)		
				ft_error(shell, EXIT, exit_mat[1]);
		close_shell(shell);
	}
	else
	{
		if (!pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_error(shell, EXIT, exit_mat[1]);
		close_shell(shell);
	}
	return (0);
}

int	more_args(char **exit_mat, t_shell *shell, pid_t pid)
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
		if (!pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_error(shell, EXIT, exit_mat[1]);
		shell->error = 2;
		close_shell(shell);
	}
	else
	{
		shell->error = 1;
		printf("minishell: exit: too many arguments\n");
	}
	return (0);
}

int	ft_exit(char **exit_mat, t_shell *shell, pid_t pid)
{
	if (matrix_len(exit_mat) < 2)
	{
		if (!pid)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		close_shell(shell);
	}
	else if (matrix_len(exit_mat) < 3)
	{
		if (!two_args(exit_mat, shell, pid))
			return (0);
	}
	else if (matrix_len(exit_mat) > 2)
	{
		if (!more_args(exit_mat, shell, pid))
			return (0);
	}
	return (0);
}
