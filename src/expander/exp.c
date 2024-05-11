/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:38 by nromito           #+#    #+#             */
/*   Updated: 2024/05/11 16:51:16 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//echo "$USER ciao come stai" | ls | cat
// $USER si salva in str, poi si usa un altra stringa per scorrere input
// e quando trova $ fa il replace di user con nromito, dopo aver mallocato 
// per Input  - var. ambiente + 1($) + strlen di result; 

void	expand_value(t_shell *shell, t_token *token, int (*r))
{
	char *str;
	char *tmp;

	(void)*r; // <----- (ciuschi) l'ho messo perche mi dava unused variable in compilazione
	token->start++;
	str = getenv(shell->input);
	if (str)
		tmp = ft_strdup(str);
}