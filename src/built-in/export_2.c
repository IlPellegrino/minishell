/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:09:04 by nromito           #+#    #+#             */
/*   Updated: 2024/06/04 12:13:44 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	it_exist(char *new_var, t_shell *shell)
{
	int	i;
	int	len;

	i = -1;
	len = -1;
	while (new_var[++len] && new_var[len] != '=' && new_var[len] != '+')
		;
	while (shell->envp[++i])
		if (!ft_strncmp(shell->envp[i], new_var, len + 1))
			return (1);
	return (0);
}

char	*create_var(char *new_var, char *new_str)
{
	int	j;
	int	pos;

	pos = -1;
	j = -1;
	new_str = ft_calloc(sizeof (char *), ft_strlen(new_var) + 1);
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
			shell->envp[i] = create_var(new_var, shell->envp[i]);
			collect_garbage(shell, shell->envp[i], 0);
		}
	}
}
