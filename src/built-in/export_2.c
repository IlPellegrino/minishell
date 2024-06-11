/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:09:04 by nromito           #+#    #+#             */
/*   Updated: 2024/06/11 16:25:58 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	count_len(char *str)
{
	int	len;

	len = -1;
	while (str[++len] && str[len] != '=' && str[len] != '+')
		;
	return (len);
}

int	it_exist(char *new_var, t_shell *shell)
{
	int	i;
	int	len;
	int	len1;

	i = -1;
	len = count_len(new_var);
	if (new_var[len] == '\0')
		while (shell->envp[++i])
			if (!ft_strncmp(shell->envp[i], new_var, len + 1))
				return (1);
	i = -1;
	while (shell->envp[++i])
	{
		if (!ft_strncmp(new_var, shell->envp[i], len))
		{
			len1 = count_len(shell->envp[i]);
			if (len == len1)
				return (1);
		}
	}
	return (0);
}

char	*create_var(char *new_var, char *new_str)
{
	int	j;
	int	pos;

	pos = -1;
	j = -1;
	new_str = ft_calloc(sizeof (char *), ft_strlen(new_var) + 1);
	if (!new_str)
		return (NULL);
	while (new_var[++j])
		new_str[++pos] = new_var[j];
	return (new_str);
}

void	change_var(char *new_var, t_shell *shell)
{
	int	i;
	int	len;

	i = -1;
	len = -1;
	while (new_var[++len] && new_var[len] != '=')
		;
	if (new_var[len] == '\0')
		return ;
	while (shell->envp[++i])
	{
		if (!ft_strncmp(shell->envp[i], new_var, len))
		{
			if (len == count_len(shell->envp[i]))
			{
				shell->envp[i] = create_var(new_var, shell->envp[i]);
				collect_garbage(shell, shell->envp[i], 0);
			}
		}
	}
	shell->envp[i] = NULL;
}
