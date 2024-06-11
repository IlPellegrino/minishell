/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:09:40 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/11 12:36:18 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	close(STDIN_FILENO);
	g_sig_type = SIG_C;
}

void	ctrl_quit(int sig)
{
	(void)sig;
	if (g_sig_type <= 1)
	{
		write(2, "\b\b  \b\b", 6);
		return ;
	}
	write(2, "Quit (core dumped)\n", 20);
	g_sig_type = 4;
}

void	get_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_quit);
}
