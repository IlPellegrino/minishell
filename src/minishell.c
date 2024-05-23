/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/23 15:47:33 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	set_arrow(t_shell *shell)
{
	if (!shell->error)
		shell->arrow = GREEN_ARROW;
	else
		shell->arrow = RED_ARROW;
	printf("%s ", shell->arrow);
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
		get_signal();
		set_arrow(&shell);
		shell.input = ft_readline(MINISHELL);
		if (!shell.input)
			close_shell(&shell);
		collect_garbage(&shell, shell.input, 0);
		get_path(&shell);
		if (shell.input)
		{
			if (lexer(&shell) && parsing(&shell) && executor(&shell))
			{
				if (shell.cmd_table)
					free_cmd_table(&shell);
				shell.error = 0;
				continue ;
			}
			if (shell.cmd_table)
				free_cmd_table(&shell);
		}
	}
}
