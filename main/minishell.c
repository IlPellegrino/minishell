/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/04/30 10:21:10 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int	main(char **envp)
{
	int		again;
	char	*input;
	char	*output;

	while (1)
	{
		again = 1;
		input = lexer();
		while (again != 0)
		{
			again = 0;
			output = expander(input);
			executor(output);
			// if input error | if no input
		}
		if ()
		{
			
			free(input);
		}
	}	
}
