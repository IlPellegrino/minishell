/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:45:12 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/29 17:25:44 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


char	*here_expand(char *str, int start)
{
	char	*new_str;
	char	*before;
	int		i;
	int		count;
	char	*expand;
	char	*after;
	char	*after_expand;
	char	*temp;
	int		len;

	count = 0;
	i = start;
	while (str[++i] && (ft_isalpha(str[i]) || str[i] == US))
		count++;
	if (!count)
		count = 1;
	expand = ft_calloc(sizeof(char *), count + 1);
	if (!expand)
		return(0);
	/* ---- copy all the previous string until the $ ----*/
	before = ft_calloc(sizeof(char *), (start) + 1);
	if (!before)
		return(0);
	i = -1;
	while (++i < start)
		before[i] = str[i];
	printf("before = %s\n", before);

	/* ---- copy the string to expand ---- */
	i = -1;
	while (++i < count)
		expand[i] = str[++start];
	printf("to expand = %s\n", expand);
	after_expand = getenv(expand);
	if (!after_expand)
		after_expand = "";
	printf("after expand = %s\n", after_expand);
	/* ---- concatenate everything ---- */
	new_str = ft_strjoin(before, after_expand);
	printf("concat expansion = %s\n", new_str);
	len =  (ft_strlen(str) - ft_strlen(new_str));
	if (len <= 0)
		len = 1;
	after = ft_calloc(sizeof(char *), len + 1);
	i = -1;
	while (str[++start])
		after[++i] = str[start];
	printf("after = %s\n", after);
	temp = ft_strdup(new_str);
	free(new_str);
	new_str = ft_strjoin(temp, after);
	free(temp);
	free(str);
	free(after);
	free(expand);
	free(before);
	printf("new str return %s \n", new_str);
	return (new_str);
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
			//if (i > (int)ft_strlen(line))
			//	break ;
			//free(final_str);
		}
	}
	free(temp);
	free(line);
	printf("new_str = %s\n", final_str);
	return (final_str);
}
