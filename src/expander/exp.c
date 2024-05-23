/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:38 by nromito           #+#    #+#             */
/*   Updated: 2024/05/23 15:13:43 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*create_new_var(t_shell *shell, char *input, int n)
{
	int		k;
	char	*result;
	char	*env_var;

	k = -1;
	if (input[n + 1] == '?' && (input[n + 2] == '\0' || input[n + 2] == DQ))
	{
		if (shell->error != 0)
			result = ft_itoa(shell->error);
		else
			return ("0");
	}
	else
	{
		env_var = ft_calloc(sizeof (char *), ft_strlen(input));
		while (input[++n] != SPACE && input[n] != '>'
			&& input[n] != PIPE && input[n] != '<'
			&& input[n] != '$' && input[n] != DQ && input[n] != SQ && input[n])
			env_var[++k] = input[n];
		result = getenv(env_var);
		collect_garbage(shell, env_var, 0);
	}
	if (result == NULL)
		return ("");
	return (result);
}

void	recreate_str(t_token *token, int j, char *input, char *new_var)
{
	int		n;
	int		k;
	char	*old_str;

	n = 0;
	k = 0;
	old_str = input;
	while (n < j)
		token->index[token->wrd][k++] = old_str[n++];
	n = 0;
	if (new_var[n] == '\0')
		token->index[token->wrd][k] = new_var[n];
	while (new_var[n])
		token->index[token->wrd][k++] = new_var[n++];
	while (old_str[++j] != SPACE && old_str[j] != '>'
		&& old_str[j] != PIPE && old_str[j] != '<'
		&& old_str[j] != '$' && old_str[j] != SQ
		&& old_str[j] != DQ && old_str[j])
		;
	while (old_str[j])
		token->index[token->wrd][k++] = old_str[j++];
}

char	*ft_allocate(t_token *token, char *input, char *new_var)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(input);
	len2 = ft_strlen(new_var);
	token->index[token->wrd] = ft_calloc(sizeof (char *), len1 + len2);
	return (token->index[token->wrd]);
}

void	expand_value(t_shell *shell, t_token *token, char *input, int j)
{
	char	*new_var;

	new_var = create_new_var(shell, input, j);
	collect_garbage(shell, new_var, 0);
	if (!new_var)
		return ;
	collect_garbage(shell, token->index[token->wrd], 0);
	token->index[token->wrd] = ft_allocate(token, input, new_var);
	if (!token->index[token->wrd])
		return ;
	recreate_str(token, j, input, new_var);
	input = token->index[token->wrd];
}

void	expand_values(t_shell *shell, t_token *token)
{
	int		j;
	char	*input;

	j = -1;
	input = token->index[token->wrd];
	while (input[++j])
	{
		if (input[j] == SQ)
			while (input[++j] != SQ)
				;
		else if (input[j] == DQ)
		{
			while (input[++j] != DQ)
				if (input[j] == '$')
					expand_value(shell, token, input, j);
		}
		else if (input[j] == '$')
			expand_value(shell, token, input, j);
	}
}
