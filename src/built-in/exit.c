/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:42:41 by nromito           #+#    #+#             */
/*   Updated: 2024/06/25 16:57:59 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

long long	ft_atoi_mod(int flag, const char *str)
{
	int			i;
	long long	number;
	long long	neg;
	int			is_neg;

	neg = 1;
	number = 0;
	i = 0;
	is_neg = 0;
	while (ft_isspace(str[i]))
		i++;
	neg = check_sign(str, &i, &is_neg);
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while (str[i] <= '9' && str[i] >= '0')
	{
		number = number * 10 + (str[i++] - 48);
		if (flag && ((number < 0 && neg == 1)
				|| ((number > 0 && neg == -1) && is_neg == 0)))
			return (0);
	}
	number *= neg;
	return (number);
}

void	first_case(t_shell *shell, char **exit_mat, pid_t pid)
{
	if (!exit_mat[1][0])
	{
		ft_error(shell, EXIT, exit_mat[1]);
		close_shell(shell);
	}
	shell->error = (ft_atoi_mod(0, exit_mat[1]) % 256);
	if (shell->error == -1 && ft_strncmp(exit_mat[1], "-1", 3))
	{
		ft_error(shell, EXIT, exit_mat[1]);
		close_shell(shell);
	}
	if (!pid)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if ((ft_atoi_mod(1, exit_mat[1]) == 0 && exit_mat[1][0] != '0'
		&& ft_strlen(exit_mat[1]) != 1))
		ft_error(shell, EXIT, exit_mat[1]);
	close_shell(shell);
}

int	two_args(char **exit_mat, t_shell *shell, pid_t pid)
{
	int	i;

	i = -1;
	while (exit_mat[1][++i])
		if (!ft_isdigit(exit_mat[1][i]) && exit_mat[1][0] != '-'
			&& exit_mat[1][0] != '+')
			break ;
	if (!exit_mat[1][i])
		first_case(shell, exit_mat, pid);
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
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	return (0);
}

int	ft_exit(char **exit_mat, t_shell *shell, pid_t pid)
{
	t_exec	*exec;

	exec = shell->executor;
	reset_io(exec);
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
