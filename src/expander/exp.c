/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:38 by nromito           #+#    #+#             */
/*   Updated: 2024/06/03 11:09:53 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	to_expand(int i, char	*line)
{
	if ( line[i + 1] == SQ
		|| line[i + 1] == DQ
		|| ft_isalnum(line[i + 1])
		|| line[i + 1] == US
		|| line[i + 1] == '$'
		|| line[i + 1] == '?')
		return(1);
	return (0);
}
void	expand_values(t_shell *shell, t_token *token)
{
	int		i;
	char	*final_str;
	char	*line;
	int		dq;
	int		sq;

	sq = 0;
	dq = 0;
	line = token->index[token->wrd];
	final_str = 0;
	if (!ft_strchr(line, '$'))
		return ;
	i = -1;
	while (line[++i])
	{
		if (line[i] == SQ && sq)
			sq = 0;
		else if (line[i] == SQ && !dq)
			sq = 1;
		else if (line[i] == DQ && dq)
		{
			dq = 0;
			sq = 0;
		}
		else if (line[i] == DQ)
			dq = 1;
		printf("sq %d\n", sq);
		if (line[i] == '$' && line[i + 1] && !sq && to_expand(i, line))
		{
			if (final_str)
				free(final_str);
			final_str = here_expand(shell, line, i);
			line = ft_strdup(final_str);
			dq = 0;
			sq = 0;
			i = -1;
		}
	
	}
	if (!final_str)
		final_str = line;
	token->index[token->wrd] = final_str;
}

