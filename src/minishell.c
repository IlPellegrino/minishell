/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/22 11:33:04 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

	init_structs(&shell);
	shell.arrow = ft_calloc(sizeof(char *), ft_strlen(GREEN_ARROW) + 1);
	collect_garbage(&shell, shell.arrow, 0);
	shell.arrow = GREEN_ARROW;
	(void)argc;
	(void)argv;
	shell.envp = envp;
	while (1)
	{
		get_signal();
		printf("%s", shell.arrow);
		shell.arrow = GREEN_ARROW;
		shell.input = ft_readline(MINISHELL);
		if (!shell.input)
			close_shell(&shell);
		collect_garbage(&shell, shell.input, 0);
		get_path(&shell);
		if (shell.input)
		{
			lexer(&shell);
			if (!parsing(&shell))
				shell.arrow = RED_ARROW;
			if (shell.cmd_table)
				free_cmd_table(&shell);
		}
	}
}
