/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:59:01 by ciusca            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/04 16:48:20 by ciusca           ###   ########.fr       */
=======
/*   Updated: 2024/06/04 16:40:24 by nromito          ###   ########.fr       */
>>>>>>> c0b735dedcdd538715f6d5e487be7e7a35d6f00b
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	set_token(t_shell *shell, t_token *token, int *i, int *command)
{
	if (find_cmd_path(shell, token->index[*i], *i) && *command == 0)
	{
		*command = 1;
		token->tokens[*i] = 'C';
	}
	else if (!(ft_strncmp(token->index[*i], "<<", 3)) && token->flag[*i] == '0')
		token->tokens[*i] = 'H';
	else if (!(ft_strncmp(token->index[*i], ">>", 3)) && token->flag[*i] == '0')
		token->tokens[*i] = 'A';
	else if (!(ft_strncmp(token->index[*i], ">", 2)) && token->flag[*i] == '0')
		token->tokens[*i] = 'O';
	else if (!(ft_strncmp(token->index[*i], "<", 2)) && token->flag[*i] == '0')
		token->tokens[*i] = 'I';
	else if (!(ft_strncmp(token->index[*i], "||", 3)))
		return (ft_error(shell, SYNTAX, token->index[*i]));
	else if (token->index[*i][0] == '|' && token->flag[*i] == '0')
	{
		*command = 0;
		token->tokens[*i] = 'P';
	}
	else
		token->tokens[*i] = 'S';
	return (1);
}
int	tokenizer(t_shell *shell)
{

	t_token	*token;
	int		i;
	int		command;

	command = 0;
	token = shell->tokens;
	token->tokens = ft_calloc(sizeof(char *), matrix_len(token->index) + 1);
	if (!token->tokens)
		return (0);
	collect_garbage(shell, token->tokens, 0);
	i = -1;
	while (token->index[++i])
		if (!set_token(shell, token, &i, &command))
			return (0);
	printf("tokens = %s\n", token->tokens);
	command = 0;
	return (1);
}
