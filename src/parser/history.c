/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 01:50:29 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/24 03:03:31 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_history(t_shell *shell)
{
	char	*line;

	shell->fd_h = open(HISTORY_FILE , O_CREAT | O_RDWR, 0777);
	if (shell->fd_h == -1)
	{
		perror("minishell");		
		return (0);
	}
	line = get_next_line(shell->fd_h);
	while (line)
	{
		free(line);
		line = get_next_line(shell->fd_h);	
	}
	free(line);
	return (1);
}

int	ft_history(void)
{
	int		fd;
	char	*line;

	fd = open(HISTORY_FILE , O_CREAT | O_RDWR, 0777);
	if (fd == -1)
	{
		perror ("minishell");
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);	
	}
	free(line);
	return (1);
}

void	update_history(t_shell *shell)
{
	return ;
	write(shell->fd_h, shell->input, ft_strlen(shell->input));
	write (shell->fd_h, "\n", 1);
	add_history(shell->input);
}
