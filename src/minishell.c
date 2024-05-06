/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/06 13:57:09 by ciusca           ###   ########.fr       */
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
		//todo: garbage collector
		shell.input = ft_readline(MINISHELL);
		find_path(&shell);
		if (shell.input)
		{
			lexer(&shell);
			//parser();
			//executor
		}
		//se input e' null semplicemente ti riparte il while
	}
}