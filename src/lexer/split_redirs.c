/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:04:00 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/25 19:18:47 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	found_redir(int c)
{
	return (c == '<' || c == '>');
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
			{
				i++;	
				count++;
			}
			else
				count++;
		}
	}
	return (ft_strlen(str) + count);
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
	while (shell->input[++i])
	{
		if (found_redir(shell->input[i]))
		{
			while (found_redir(shell->input[i]) && len < 2)
			{
				i++;
				len++;
				new_str[j++] = shell->input[i];
			}
			new_str[j++] = ' ';
		}
		new_str[j] = shell->input[i];
			
	}
	printf("new str %s\n", new_str);
}
