/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:09:04 by nromito           #+#    #+#             */
/*   Updated: 2024/06/12 12:28:53 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_export(char *to_check, t_shell *shell)
{
	int	flag;
	int	pos;

	flag = 2;
	pos = -1;
	while (to_check[++pos])
	{
		if (to_check[pos] == '+' && to_check[pos + 1] == '=')
			flag = 1;
		else if ((!ft_isalnum(to_check[pos]) && to_check[pos] != US
			&& to_check[pos] != '+' && to_check[pos] != '=')
			|| (ft_isdigit(to_check[0]) || to_check[0] == '+'
				|| to_check[0] == '='))
		{
			ft_error(shell, EXPORT, to_check);
			flag = 0;
			return (flag);
		}
		else if (to_check[pos] == '=')
			break ;
	}
	return (flag);
}

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

char	*create_var(char *new_var)
{
	int		j;
	int		pos;
	char	*new_str;

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
				free(shell->envp[i]);
				shell->envp[i] = create_var(new_var);
			}
		}
	}
	shell->envp[i] = NULL;
}
