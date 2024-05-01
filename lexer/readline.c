/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:55 by nromito           #+#    #+#             */
/*   Updated: 2024/04/30 12:24:37 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

char *lexer()
{
	char *input;

	input = readline("minishell: ");
	if (input != NULL)
	{
		tokenizer(input);
		parser(input);
		if (input == NULL)
			return (input);
		add_history(input);
		rl_on_new_line();
	}
	else
		printf("%s: command not found\n", input);
	return (input);
}

void	tokenizer(char *input)
{
	char	**matrix_input;

	matrix_input = ft_split()
}
