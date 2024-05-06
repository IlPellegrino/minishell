/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:46:29 by nromito           #+#    #+#             */
/*   Updated: 2024/05/06 10:55:09 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// checker for even/odd quotes
int	quotes_checker(t_shell *shell)
{
	char	*tmp;
	int		j;
	int		i;

	i = -1;
	j = 0;
	tmp = shell->input;
	while (tmp[++i])
	{
		if (tmp[i] == 34 || tmp[i] == 39)
			j += 1;
	}
	if (j % 2 == 0)
		return (1);
	else
		return (0);
}

// needs to be checked and finished, just made the first part of it.
void	checker(t_shell *shell)
{
	t_token	token;
	int		i;
	int		j;
	int		k;
	
	i = -1;
	j = 0;
	while (shell->input[++i])
	{
		while (shell->input[i] == 32)
			i++;
		if (shell->input[i] == 34 || (shell->input[i] == 39
			&& shell->input[i + 1] == 34) || shell->input[i + 1] == 39)
		{
			token.index[j][k] = '\0';
			j++;
			i += 2;
		}
		else if (shell->input[i] == 34 || (shell->input[i] == 39 && shell->input[i + 1] != 34) || shell->input[i + 1] != 39)
		{
			i++;
			k = 0;
			while ((shell->input[i] != '\0'
				&& (shell->input[i] != 34)) || shell->input[i] != 39)
			{
				token.index[j][k] = shell->input[i];
				k++;
				i++;
			}
			token.index[j][k] = '\0';
			j++;
		}
		else if (shell->input[i] != 32)
		{
			while (shell->input[i] != 32)
			{
				if (shell->input[i] == 34 || shell->input == 39)
					i++;
				token.index[j][k++] = shell->input[i++];
			}
			token.index[j][k] = '\0';
			j++;
		}
	}
}
