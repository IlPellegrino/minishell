/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:00:17 by nromito           #+#    #+#             */
/*   Updated: 2024/06/07 12:18:28 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	n_flag(char **echo_mat)
{
	int	pos;
	int	i;

	pos = 1;
	i = 0;
	while (echo_mat[pos])
	{
		if (echo_mat[pos][0] == '-')
		{
			while (echo_mat[pos][++i] && echo_mat[pos][i] == 'n')
				;
			if (echo_mat[pos][i] == '\0' && i > 1)
			{
				pos++;
				i = 0;
			}
			else
				break ;
		}
		else
			break ;
	}
	pos -= 1;
	return (pos);
}

int	ft_echo(char **echo_mat)
{
	int	pos;

	pos = 0;
	if (!n_flag(echo_mat))
	{
		while (echo_mat[++pos])
		{
			if (pos > 1)
				printf(" ");
			printf("%s", echo_mat[pos]);
		}
		printf("\n");
	}
	else if (n_flag(echo_mat))
	{
		pos += n_flag(echo_mat);
		while (echo_mat[++pos])
		{
			if (pos > 1 + n_flag(echo_mat))
				printf(" ");
			printf("%s", echo_mat[pos]);
		}
	}
	return (1);
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
		return (0);
}
