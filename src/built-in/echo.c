/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:00:17 by nromito           #+#    #+#             */
/*   Updated: 2024/05/21 14:43:57 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//bisogna passare anche la posizione all'interno della matrice(token->wrd),
// per sapere echo dove sta.

// void	ft_echo(t_shell *shell, t_token *token, int pos)
// {
// 	int	i;

// 	i = -1;
// 	while (token->index[++pos])
// 	{
// 		while (token->index[pos][++i])
// 		{
// 			if (token->index[pos][i] == '<' || token->index[pos][i] == '>'
// 				|| token->index[pos][i] == PIPE)
// 				break;
// 			if ()
// 		}
// 	}
// }