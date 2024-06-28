/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:04:00 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/28 14:15:34 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	found_redir(int c)
{
	return (c == '<' || c == '>');
}

int	manage_quotes(char *str, int end)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (str[++i] && i < end)
	{
		if (str[i] == SQ || (str[i] == DQ && !quote))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
	}
	return (quote);
}

int	count_split_redirs(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (found_redir(str[i]))
		{
			if (found_redir(str[i + 1]))
				i++;
			if (!ft_isspace(str[i + 1]))
				count++;
		}
	}
	return (ft_strlen(str) + count);
}

char	*perform_split(t_shell *shell, int len, char *new_str)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (shell->input[++i])
	{
		while (found_redir(shell->input[i]) && len < 2
			&& !manage_quotes(shell->input, i))
		{
			len++;
			new_str[j++] = shell->input[i++];
			if (len == 2 || !found_redir(shell->input[i]))
			{
				if (shell->input[i] != ' ')
					new_str[j++] = ' ';
				len = 0;
			}
		}
		new_str[j++] = shell->input[i];
		if (!shell->input[i])
			return (new_str);
	}
	return (new_str);
}

void	split_redirs(t_shell *shell)
{
	int		i;
	int		len;
	char	*new_str;
	int		j;

	j = 0;
	len = 0;
	new_str = ft_calloc(sizeof(char *), count_split_redirs(shell->input) + 1);
	if (!new_str)
		return ;
	i = -1;
	new_str = perform_split(shell, len, new_str);
	shell->input = ft_strdup(new_str);
	free(new_str);
	collect_garbage(shell, shell->input, 0);
}
