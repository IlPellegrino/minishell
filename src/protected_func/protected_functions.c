/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:02:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/13 11:30:23 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	fork_p(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	return (pid);
}

void	execve_p(char *cmd_path, char **argv, char **envp)
{
	if (execve(cmd_path, argv, envp) == -1)
		return ;
}

void	pipe_p(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
		return ;
}

void	wait_p(int *status)
{
	if (wait(status) == -1)
		return ;
}

int	access_p(char *file, int mode)
{
	int	ret;

	ret = access(file, mode);
	if (ret == -1 && errno != ENOENT)
		return (0);
	return (ret);
}

void	close_fds(void)
{
	int	i;

	i = 0;
	while (i < 1024)
		close(i++);
}
