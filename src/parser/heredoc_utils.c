/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:45:12 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/28 18:42:45 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*copy_expanded(char *expanded, char *final_line, int *j)
{
	int	i;

	i = -1;
	while (expanded[++i])
		final_line[(*j)++] = expanded[i];
	free(expanded);
	return (final_line);
}

char	*expand_var(char *line, int *i)
{
	char	*temp_str;
	char	*expanded;
	int		count;
	int		j;

	j = (*i);
	count = 0;
	while (ft_isalpha(line[++j]) || line[j] == US)
		count++;
	temp_str = ft_calloc(sizeof(char *), count + 1);
	if (!temp_str)
		return (0);
	count = 0;
	while (++(*i) < j)
		temp_str[count++] = line[(*i)];
	(*i)--;
	if (!ft_strncmp(temp_str, "$", ft_strlen(temp_str)))
		expanded = expand_pid();
	else
		expanded = ft_strdup(getenv(temp_str));
	if (!expanded)
		expanded = "";
	free(temp_str);
	return (expanded);
}

int	find_len(char *line)
{
	int		final_len;
	int		i;
	char	*expanded;

	i = -1;
	final_len = 0;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			if (ft_isdigit(line[i + 1]))
			{
				i++;
				continue ;
			}
			expanded = expand_var(line, &i);
			final_len += ft_strlen(expanded);
			free(expanded);
		}
		else
			final_len++;
	}
	return (final_len);
}

char	*expand_heredoc(char *line)
{
	int		i;
	char	*final_str;
	int		j;

	j = 0;
	i = -1;
	final_str = ft_calloc(sizeof(char *), find_len(line) + 1);
	if (!final_str)
		return (0);
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			if (ft_isdigit(line[i + 1]))
			{
				i++;
				continue ;
			}
			final_str = copy_expanded(expand_var(line, &i), final_str, &j);
		}
		else
			final_str[j++] = line[i];
	}
	free(line);
	printf("new_str = %s\n", final_str);
	return (final_str);
}
