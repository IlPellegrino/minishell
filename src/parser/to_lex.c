/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_lex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:08:18 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/22 14:27:22 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*make_string(char **mat)
{
	char	*new_str;
	char	*temp;
	int		i;

	new_str = ft_strdup(mat[0]);
	i = 0;
	while (mat[++i])
	{
		temp = ft_strjoin(new_str, " ");
		free(new_str);
		new_str = ft_strjoin(temp, mat[i]);
		free(temp);
	}
	return (new_str);
}

int	to_lex(t_shell *shell)
{
	int		i;
	t_token	*token;

	token = shell->tokens;
	i = -1;
	while (token->index[++i])
	{
		if (count_words(token->index[i]) > 1 && token->flag[i] == '0')
		{
			shell->input = make_string(token->index);
			collect_garbage(shell, shell->input, 0);
			return (1);
		}
	}
	return (0);
}
