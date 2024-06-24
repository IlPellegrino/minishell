/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_lex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:08:18 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/24 18:02:19 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_token(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (1);
	else if (!ft_strncmp(str, ">>", 2))
		return (1);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (1);
	else if (!ft_strncmp(str, "|", 1))
		return (1);
	return (0);
}

int	count_token(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (get_token(str + i))
			count++;
	}
	return (ft_strlen(str) + (count * 4));
}

char	*check_tokens(char *str)
{
	int		i;
	char	*new_str;
	int		j;

	new_str = ft_calloc(sizeof(char), count_token(str) + 1);
	if (!new_str)
		return (0);
	j = 0;
	i = -1;
	while (str[++i])
	{
		if (get_token(str + (i + 1)))
		{
			new_str[j++] = ' ';
			new_str[j++] = '\"';
			while (!ft_isspace(str[++i]))
				new_str[j++] = str[i];
			new_str[j++] = '\"';
			new_str[j++] = ' ';
			continue ;
		}
		new_str[j++] = str[i];
	}
	free(str);
	return (new_str);
}

char	*make_string(char **mat, int j)
{
	char	*new_str;
	char	*temp;
	int		i;

	i = 0;
	mat[j] = check_tokens(mat[j]);
	new_str = ft_strdup(mat[0]);
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
			shell->input = make_string(token->index, i);
			collect_garbage(shell, shell->input, 0);
			return (1);
		}
	}
	return (0);
}
