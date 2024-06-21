/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:38 by nromito           #+#    #+#             */
/*   Updated: 2024/06/21 18:39:32 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	to_expand(int i, char *line, int dq, int sq)
{
	if ((line[i + 1] == SQ && line[i + 2] && !sq)
		|| (line[i + 1] == DQ && line[i + 2] && !dq)
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
	}
	else if (line_pos == DQ)
		exp->dq = 1;
}

int	init_exp(t_token *token, t_exp *exp)
{
	//printf("exp->line %s\n", exp->line);
	exp->sq = 0;
	exp->dq = 0;
	exp->line = token->index[token->wrd];
	exp->final_str = 0;
	if (!ft_strchr(exp->line, '$'))
		return (1);
	else if (token->wrd > 0
		&& !ft_strncmp(token->index[token->wrd - 1], "<<", 3))
		return (1);
	return (0);
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

	if (init_exp(token, &exp))
		return ;
	i = -1;
	while (exp.line[++i])
	{
		quotes_handler(exp.line[i], &exp);
		if (exp.line[i] == '$' && exp.line[i + 1]
			&& !exp.sq && to_expand(i, exp.line, exp.dq, exp.sq))
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
	//printf("expanded = %s\n", exp.final_str);
	token->index[token->wrd] = exp.final_str;
}
