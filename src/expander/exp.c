/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:38 by nromito           #+#    #+#             */
/*   Updated: 2024/06/20 11:53:06 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	to_expand(int i, char *line)
{
	if (line[i + 1] == SQ
		|| line[i + 1] == DQ
		|| ft_isalnum(line[i + 1])
		|| line[i + 1] == US
		|| line[i + 1] == '$'
		|| line[i + 1] == '?')
		return (1);
	return (0);
}

void	quotes_handler(char line_pos, t_exp *exp)
{
	if (line_pos == SQ && exp->sq)
		exp->sq = 0;
	else if (line_pos == SQ && !exp->dq)
		exp->sq = 1;
	else if (line_pos == DQ && exp->dq)
	{
		exp->dq = 0;
		exp->sq = 0;
	}
	else if (line_pos == DQ)
		exp->dq = 1;
}

void	init_exp(t_token *token, t_exp *exp)
{
	exp->sq = 0;
	exp->dq = 0;
	exp->line = token->index[token->wrd];
	exp->final_str = 0;
}

void	re_init(t_exp *exp, int *i)
{
	exp->dq = 0;
	exp->sq = 0;
	*i = -1;
}

void	expand_values(t_shell *shell, t_token *token)
{
	int		i;
	t_exp	exp;

	init_exp(token, &exp);
	printf("line = %s\n", exp.line);
	if (!ft_strchr(exp.line, '$'))
		return ;
	else if (token->wrd > 0 && !ft_strncmp(token->index[token->wrd - 1], "<<", 3))
		return ;
	i = -1;
	while (exp.line[++i])
	{
		quotes_handler(exp.line[i], &exp);
		if (exp.line[i] == '$' && exp.line[i + 1]
			&& !exp.sq && to_expand(i, exp.line))
		{
			if (exp.final_str)
				free(exp.final_str);
			exp.final_str = here_expand(shell, exp.line, i);
			free(exp.line);
			exp.line = ft_strdup(exp.final_str);
			re_init(&exp, &i);
		}
	}
	if (!exp.final_str)
		exp.final_str = ft_strdup(exp.line);
	free(exp.line);
	token->index[token->wrd] = exp.final_str;
}
