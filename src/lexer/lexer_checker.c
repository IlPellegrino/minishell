/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:46:29 by nromito           #+#    #+#             */
/*   Updated: 2024/05/06 15:41:24 by ciusca           ###   ########.fr       */
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
	
	k = 0;
	i = -1;
	j = 0;
	while (shell->input[++i])
	{
		while (shell->input[i] == 32)
			i++;
		if ((shell->input[i] == DQ || shell->input[i] == SQ)
			&& (shell->input[i + 1] == DQ || shell->input[i + 1] == SQ))
		{
			printf("double\n");
			token.index[j][k] = '\0';
			j++;
			i++;
		}
		else if ((shell->input[i] == DQ || shell->input[i] == SQ) && ((shell->input[i + 1] != DQ) || shell->input[i + 1] != SQ))
		{
			i++;
			k = 0;
			printf("i %d\n", i);
			while ((shell->input[i] != '\0'
				&& (shell->input[i] != DQ)) || shell->input[i] != SQ)
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
			printf("qui\n");
			while (shell->input[i] != 32 && shell->input[i])
			{
				if (shell->input[i] == DQ || shell->input[i] == SQ)
					i++;
				token.index[j][k++] = shell->input[i++];
			}
		}
	}
	for(int i = 0; token.index[i]; i++)
		printf("token.index[i] = %s\n", token.index[i]);
	
}
