/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/07 17:07:50 by ciusca           ###   ########.fr       */
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
	t_shell	shell;
	//char	*input;
	//init shell;
	shell.envp = envp;
	if (argv[1])
		argc = 2;
	argc++;
	while(1)
	{
		//get_signal();
		get_signal();
		//todo: garbage collector
		shell.input = ft_readline(MINISHELL);
		if (!shell.input)
			return (printf("exit\n"), 0);
		get_path(&shell);
		if (shell.input)
		{
			//find_path(&shell);
			lexer(&shell);
			//shell.tokens.index = ft_split(shell.input, 32);
			//parsing(&shell);
		/*if (shell.input)
		{
			//lexer(&shell);
			//parser();
>>>>>>> 38abf0c34da8dbdf5a9ed543e6f810bf1884571a
			//executor
		}*/
		}
	}
}