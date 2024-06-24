/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:09:40 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/23 22:40:18 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	if (g_sig_type == 0 || g_sig_type == SIG_C)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sig_type == 42)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	else if (g_sig_type == 1)
	{
		write(1, "\n", 1);
		//g_sig_type = 19;
		//rl_on_new_line();
		//rl_replace_line("", 0);
		close(0);
		//return ;
	}
	else
		write (1, "\n", 1);
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
