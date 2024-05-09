/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:02:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/09 16:48:13 by ciusca           ###   ########.fr       */
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

void	ft_error(char *msg, int id)
{
	if (!msg)
		perror("Error");
	else
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	close_fds();
	if (id == 127)
		free(msg);
	exit(id);
}

void	error_lexer(char *msg, int id, t_shell *shell)
{
	free_matrix(shell->tokens->index);
	if (!msg)
		perror("Error");
	else
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	exit (id);
}

void	close_fds(void)
{
	int	i;

	i = 0;
	while (i < 1024)
		close(i++);
}
