/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/06/11 11:38:50 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_sig_type;

void	set_arrow(t_shell *shell)
{
	if (!shell->error)
		shell->arrow = GREEN_ARROW;
	else
		shell->arrow = RED_ARROW;
	printf("%s", shell->arrow);
}

char	*ft_readline(char *str)
{
	char	*input;

	input = readline(str);
	if (!input)
		return (0);
	add_history(input);
	rl_on_new_line();
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	init_structs(&shell, argc, argv, envp);
	while (JESUS)
	{
		g_sig_type = 0;
		shell.len = 0;
		get_signal();
		set_arrow(&shell);
		shell.input = ft_readline(MINISHELL);
		if (!shell.input)
		{
			ft_putendl_fd("exit", 2);
			close_shell(&shell);
		}
		get_path(&shell);
		if (shell.input)
		{
			if (lexer(&shell) && parsing(&shell) && executor(&shell))
				shell.error = 0;
			free(shell.input);
			if (shell.cmd_table)
				free_cmd_table(&shell);
		}
	}
}
