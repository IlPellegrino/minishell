/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:02:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/10 13:59:24 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	fork_p(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error(NULL, 11);
	return (pid);
}

void	execve_p(char *cmd_path, char **argv, char **envp)
{
	if (execve(cmd_path, argv, envp) == -1)
		ft_error(NULL, 12);
}

void	pipe_p(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
		ft_error(NULL, 27);
}

void	wait_p(int *status)
{
	if (wait(status) == -1)
		ft_error(NULL, 13);
}

int	access_p(char *file, int mode)
{
	int	ret;

	ret = access(file, mode);
	if (ret == -1 && errno != ENOENT)
		ft_error(NULL, 10);
	return (ret);
}

void	close_fds(void)
{
	int	i;

	i = 0;
	while (i < 1024)
		close(i++);
}
