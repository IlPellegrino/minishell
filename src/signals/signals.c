/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:09:40 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/24 18:09:00 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*set_prompt_c(void)
{
	char	*dir;
	char	*prompt;
	char	*temp;

	temp = getcwd(NULL, 0);
	dir = ft_strdup(ft_strrchr(temp, '/'));
	free(temp);
	temp = ft_strjoin(RED_MINISHELL, dir);
	free(dir);
	prompt = ft_strjoin(temp, RESET "}");
	free(temp);
	return (prompt);
}

void	ctrl_c(int sig)
{
	char	*prompt;

	(void)sig;
	if (g_sig_type == 0 || g_sig_type == SIG_C || g_sig_type == 42)
	{
		write(1, "\n", 1);
		prompt = set_prompt_c();
		printf("%s\n", prompt);
		free(prompt);
		printf(CYAN);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sig_type == 1 || g_sig_type == 2)
	{
		write(1, "\n", 1);
		close(0);
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
