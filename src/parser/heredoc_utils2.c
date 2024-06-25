/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:45:12 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/25 13:39:06 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_two(char *alloc1, char *alloc2)
{
	free(alloc1);
	free(alloc2);
}

char	*after_exp(char *expand, int len, t_shell *shell)
{
	char	*after_expand;

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
	return (after_expand);
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
	while (str[++i] && ((ft_isalnum(str[i]) || str[i] == US)))
	{
		if (count == 0 && ft_isdigit(str[i]))
			break ;
		count++;
	}
	if (!count)
		count = 1;
	before = copy_prev(str, start);
	after = copy_str_exp(shell, count, &start, str);
	temp = ft_strdup(before);
	free(before);
	before = ft_strjoin(temp, after);
	free_two(after, temp);
	after = get_after(str, before, start);
	temp = ft_strjoin(before, after);
	return (free_two(after, before), temp);
}
