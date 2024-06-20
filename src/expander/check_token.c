/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:50:01 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/20 13:54:50 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*make_quotes(char *str)
{
	char	*temp;
	char	*final_str;

	temp = ft_strjoin("\"", str);
	free(str);
	final_str = ft_strjoin(temp, "\"");
	free(temp);
	return (final_str);
}

int	is_token(char *str)
{
	if (!ft_strncmp(str, "<<", 3))
		return (1);
	else if (!ft_strncmp(str, ">>", 3))
		return (1);
	else if (!ft_strncmp(str, "<", 2))
		return (1);
	else if (!ft_strncmp(str, ">", 2))
		return (1);
	else if (!ft_strncmp(str, "|", 2))
		return (1);
	return (0);
}