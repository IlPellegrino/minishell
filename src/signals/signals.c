/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:17:03 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/06 18:46:35 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ctrl_c(int sig)
{
	sig = 0;
	write(2, "\b\b  ", 4);
	printf("\n");
	printf(MINISHELL);
}

void	ctrl_quit(int sig)
{
	sig = 0;
	exit (1);
	
}

void	get_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}