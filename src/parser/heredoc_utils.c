/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:45:12 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/03 14:59:42 by nromito          ###   ########.fr       */
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

char	*copy_str_exp(t_shell *shell, int count, int *start, char *str)
{
	char	*after_expand;
	char	*expand;
	int		i;
	int 	len;
	
	i = -1;
	
	expand = ft_calloc(sizeof(char *), count + 1);
	if (!expand)
		return(0);
	i = -1;
	while (++i < count)
		expand[i] = str[++(*start)];
	printf("to expand = %s\n", expand);
	len = ft_strlen(expand);
	if (!len)
		len++;
	if (!ft_strncmp(expand, "$", len))
		after_expand = expand_pid();
	else if (!ft_strncmp(expand, "'", len))
		after_expand = ft_strdup("'");
	else if (!ft_strncmp(expand, "\"", len))
		after_expand = ft_strdup("\"");
	else if (!ft_strncmp(expand, "?", len))
		after_expand = ft_itoa(shell->error);
	else
		after_expand = ft_getenv(expand, shell);
	printf("expanded = %s\n",after_expand);
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

	len =  (ft_strlen(str) - ft_strlen(new_str));
	if (len <= 0)
		len = 1;
	after = ft_calloc(sizeof(char *), len + 1);
	i = -1;
	while (str[++start])
		after[++i] = str[start];
	return (after);
}

char	*here_expand(t_shell *shell, char *str, int start)
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
	after = copy_str_exp(shell, count, &start, str);
	temp = ft_strdup(before);
	free(before);
	before = ft_strjoin(temp, after);
	free(after);
	free(temp);
	after = get_after(str, before, start);
	temp = ft_strjoin(before, after);
	//free(str);
	free(after);
	free(before);
	return (temp);
}

int find_expansion(char *temp, int *start)
{
	int	i;

	i = -1;
	(void)start;
	while (temp[++i])
	{
		if (temp[i] == '$' && (ft_isalnum(temp[i + 1]) || temp[i + 1] == US))
			break ;	
	}

	return(i);
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
			temp = ft_strdup(final_str);
		}
	}
	free(temp);
	free(line);
	printf("new_str = %s\n", final_str);
	return (final_str);
}
