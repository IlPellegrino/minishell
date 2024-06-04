/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:45:12 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/04 14:54:09 by ciusca           ###   ########.fr       */
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

int	find_expansion(char *temp, int *start)
{
	int	i;

	i = -1;
	(void)start;
	while (temp[++i])
	{
		if (temp[i] == '$' && (ft_isalnum(temp[i + 1]) || temp[i + 1] == US))
			break ;
	}
	return (i);
}

char	*expand_heredoc(t_shell *shell, char *line)
{
	int		i;
	char	*final_str;
	char	*temp;

	final_str = 0;
	temp = ft_strdup(line);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			if (final_str)
				free(final_str);
			final_str = here_expand(shell, temp, find_expansion(temp, 0));
			free(temp);
			temp = ft_strdup(final_str);
		}
	}
	free(temp);
	free(line);
	return (final_str);
}
