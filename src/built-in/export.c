/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:40:46 by nromito           #+#    #+#             */
/*   Updated: 2024/06/11 15:44:14 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_addtoenv(char *new_var, t_shell *shell)
{
	int		i;

	i = -1;
	if (it_exist(new_var, shell))
		change_var(new_var, shell);
	else
	{
		while (shell->envp[++i])
			;
		shell->envp[i] = create_var(new_var, shell->envp[i]);
		shell->envp[++i] = NULL;
	}
	return (0);
}

int	join_env(char *new_var, t_shell *shell)
{
	int		i;

	i = -1;
	if (it_exist(new_var, shell))
		add_var(new_var, shell);
	else
	{
		while (shell->envp[++i])
			;
		shell->envp[i] = create_plus_var(new_var, shell->envp[i]);
		shell->envp[++i] = NULL;
	}
	return (0);
}

void	one_arg(t_shell *shell)
{
	int	pos;
	int	i;

	i = -1;
	while (shell->envp[++i])
	{
		pos = -1;
		printf("declare -x ");
		while (shell->envp[i][++pos])
		{
			if (shell->envp[i][pos] == '=')
			{
				printf("%c", shell->envp[i][pos]);
				printf("\"");
				while (shell->envp[i][++pos])
					printf("%c", shell->envp[i][pos]);
				printf("\"");
				break ;
			}
			printf("%c", shell->envp[i][pos]);
		}
		printf("\n");
	}
}

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
		else if ((!ft_isalpha(to_check[pos]) && to_check[pos] != US)
			&& (ft_isdigit(to_check[0]) || to_check[0] == '+'
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

char	**check_args(t_shell *shell, char **export_mat)
{
	int		i;
	int		words;
	char	**result;

	i = 0;
	words = 0;
	while (export_mat[++i])
		if (!it_exist(export_mat[i], shell))
			words++;
	words += 1;
	if (words == 1)
		return (shell->envp);
	result = ft_calloc(sizeof (char **), matrix_len(shell->envp) + words);
	if (!result)
		return (0);
	i = -1;
	while (shell->envp[++i])
	{
		result[i] = ft_strdup(shell->envp[i]);
		if (!result[i])
			return (0);
	}
	result[i] = NULL;
	return (result);
}

int	ft_export(char **export_mat, t_shell *shell)
{
	int		i;
	int		flag;

	if (export_mat[0])
	{
		if (matrix_len(export_mat) < 2)
			return (one_arg(shell), 1);
		i = 0;
		shell->envp = check_args(shell, export_mat);
		collect_garbage(shell, 0, shell->envp);
		while (export_mat[++i])
		{
			flag = check_export(export_mat[i], shell);
			if (flag == 0)
				return (0);
			else if (flag == 1)
				join_env(export_mat[i], shell);
			else if (flag == 2)
				ft_addtoenv(export_mat[i], shell);
		}
		return (1);
	}
	return (0);
}
