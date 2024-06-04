/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:45:12 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/30 18:12:44 by ciusca           ###   ########.fr       */
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
		return(0);
	while (++i < start)
		before[i] = str[i];
	printf("before = %s\n", before);
	return (before);
}

char	*copy_str_exp(int count, int *start, char *str)
{
	char	*after_expand;
	char	*expand;
	int		i;
	
	i = -1;
	
	expand = ft_calloc(sizeof(char *), count + 1);
	if (!expand)
		return(0);
	i = -1;
	while (++i < count)
		expand[i] = str[++(*start)];
	printf("to expand = %s\n", expand);
	if (!ft_strncmp(expand, "$", ft_strlen(expand)))
		expand = expand_pid();
	else
		expand = getenv(expand);
	after_expand = expand;
	if (!after_expand)
		after_expand = "";
	free(expand);
	return (after_expand);
}

char	*get_after(char *str, char *new_str, int start)
{
	char	*after;
	int		len;
	int		i;

	len =  (ft_strlen(str) - ft_strlen(new_str));
	if (len <= 0)
		len = 1;
	after = ft_calloc(sizeof(char *), len + 1);
	i = -1;
	while (str[++start])
		after[++i] = str[start];
	return (after);
}

char	*here_expand(char *str, int start)
{
	char	*before;
	int		i;
	int		count;
	char	*after;
	char	*temp;

	count = 0;
	i = start;
	while (str[++i] && (ft_isalpha(str[i]) || str[i] == US))
		count++;
	if (!count)
		count = 1;
	before = copy_prev(str, start);
	after = copy_str_exp(count, &start, str);
	temp = ft_strdup(before);
	free(before);
	before = ft_strjoin(temp, after);
	free(temp);
	after = get_after(str, before, start);
	temp = ft_strjoin(before, after);
	free(str);
	free(after);
	free(before);
	return (temp);
}

int find_expansion(char *temp)
{
	int	i;

	i = -1;
	while (temp[++i] && temp[i] != '$')
		;
	return(i);
}

char	*expand_heredoc(char *line)
{
	int		i;
	char	*final_str;
	int		j;
	char	*temp;

	final_str = 0;
	temp = ft_strdup(line);
	j = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1] )
		{
			if (final_str)
				free(final_str);
			final_str = here_expand(temp, find_expansion(temp));
			temp = ft_strdup(final_str);
		}
	}
	free(temp);
	free(line);
	printf("new_str = %s\n", final_str);
	return (final_str);
}
