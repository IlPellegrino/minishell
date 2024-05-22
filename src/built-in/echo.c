/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:00:17 by nromito           #+#    #+#             */
/*   Updated: 2024/05/22 12:04:57 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//bisogna passare anche la posizione all'interno della matrice(token->wrd),
// per sapere echo dove sta.

void	ft_echo(char **echo_mat)
{
	int pos;

	pos = 0;
	while (echo_mat[++pos])
	{
        if (pos > 1)
			write(1, " ", 1);
		// if (token->flag[pos] == '1' || token->flag[pos] == '2')
		// 	while (echo_mat[pos][++i])
        //         write(1, &echo_mat[pos][i], 1);
		printf("%s", echo_mat[pos]);
    }
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0') && (s2[i] != '\0'))
		i++ ;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	else
		return(0);
}


void ft_initecho(t_token *token)
{
	int	i;

	i = -1;
	while (token->index[++i])
	{
		if(ft_strcmp(token->index[i], "echo"))
		{		
			ft_echo(token, i);
			break;
		}
	}
}