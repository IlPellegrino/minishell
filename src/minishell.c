/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/10 13:46:06 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_readline(char *str)
{
	char *input;

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
	t_garbage 	*garbage;
	t_token		*token;

	token = malloc(sizeof(t_token));
	shell.tokens = token;
	garbage = malloc(sizeof(t_garbage));
	garbage->next = NULL;
	garbage->arg = 0;
	garbage->mat = 0;
	shell.collector = garbage;
	shell.envp = envp;
	if (argv[1])
		argc = 2;
	argc++;
	while(1)
	{
		get_signal();
		shell.input = ft_readline(MINISHELL);
		if (!shell.input)
			close_shell(&shell);
		collect_garbage(&shell, shell.input, 0);
		//printf("input = %s\n", shell.input);
		get_path(&shell);
		if (shell.input)
		{
			lexer(&shell);			
			parsing(&shell);
		}
	}
}