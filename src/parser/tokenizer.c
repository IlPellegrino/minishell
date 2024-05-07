/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:59:01 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/07 17:30:18 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"



int	tokenizer(t_shell *shell)
{
	t_token token;
	int		i;
	
	i = -1;
	token = shell->tokens;
	//print_matrix(token.index);
	token.tokens = ft_calloc(sizeof(char *), 10);
	printf("token.index %s", token.index[0]);
	while (token.index[++i])
	{
		printf("i = %d\n", i);
		if (find_cmd(shell, token.index[i]))
			token.tokens[i] = 'C';
		else if (!(ft_strncmp(token.index[i], "<<", 2)))
			token.tokens[i] = 'H';
		else if (!(ft_strncmp(token.index[i], ">>", 2)))
			token.tokens[i] = 'A';
		else if (ft_strchr(token.index[i], '>'))
			token.tokens[i] = 'O';
		else if (ft_strchr(token.index[i], '<'))
			token.tokens[i] = 'I';
		else if (ft_strchr(token.index[i], '|'))
			token.tokens[i] = 'P';
		else if (!(ft_strncmp(token.index[i], "-", 1) )
				&& token.tokens[i - 1] == 'C')
			token.tokens[i] = 'F';
		else
			token.tokens[i] = 'S';
	}
	printf("tokens = %s\n", token.tokens);
	return (1);
}