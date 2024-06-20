/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:45:12 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/20 11:06:41 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*copy_prev(char *str, int start)
{
	int		i;
	char	*before;

	i = -1;
	before = ft_calloc(sizeof(char *), (start) + 1);
	if (!before)
		return (0);
	while (++i < start)
		before[i] = str[i];
	return (before);
}

char	*copy_str_exp(t_shell *shell, int count, int *start, char *str)
{
	char	*after_expand;
	char	*expand;
	int		i;
	int		len;

	i = -1;
	expand = ft_calloc(sizeof(char *), count + 1);
	if (!expand)
		return (0);
	i = -1;
	while (++i < count)
		expand[i] = str[++(*start)];
	len = ft_strlen(expand);
	if (!len)
		len++;
	after_expand = after_exp(expand, len, shell);
	if (!after_expand)
		after_expand = ft_strdup("");
	free(expand);
	return (after_expand);
}

char	*get_after(char *str, char *new_str, int start)
{
	char	*after;
	int		len;
	int		i;

	len = (ft_strlen(str) - ft_strlen(new_str));
	if (len <= 0)
		len = 1;
	after = ft_calloc(sizeof(char *), len + 1);
	i = -1;
	while (str[++start])
		after[++i] = str[start];
	return (after);
}

char	*expand_heredoc(t_shell *shell, char *line)
{
	int		i;
	char	*final_str;
	char	*temp;

	final_str = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '$'))
		{
			temp = ft_strdup(line);
			free(line);
			line = here_expand(shell, temp, i);
			free(temp);
			i = -1;
		}
	}
	final_str = ft_strdup(line);
	free(line);
	return (final_str);
}
