/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/05/06 16:17:03 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/06 18:46:35 by ciusca           ###   ########.fr       */
=======
/*   Created: 2024/05/07 12:09:40 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/07 12:12:09 by ciusca           ###   ########.fr       */
>>>>>>> 70e60318b7042749678a47ee80fc9771a33d7166
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
<<<<<<< HEAD
}
=======
}
>>>>>>> 70e60318b7042749678a47ee80fc9771a33d7166
