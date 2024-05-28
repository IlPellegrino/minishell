/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:09:40 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/27 15:23:23 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	if (!g_sig_type)
	{
		write(2, "\n", 1);
		write (2, RED_ARROW, ft_strlen(RED_ARROW));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (g_sig_type == IN_HEREDOC)
	{
		write(2, "\n", 1);
		close(STDIN_FILENO);
		g_sig_type = SIG_C;
	}
}

void	ctrl_quit(int sig)
{
	(void)sig;
	exit (1);
}

void	get_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
