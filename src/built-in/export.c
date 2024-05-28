/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:40:46 by nromito           #+#    #+#             */
/*   Updated: 2024/05/28 18:44:32 by ciusca           ###   ########.fr       */
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
	{
		if (!ft_strncmp(shell->envp[i], new_var, len))
			return (1);
	}
	return (0);
}

char	*create_var(char *new_var, char *new_str)
{
	int	j;
	int	pos;

	pos = -1;
	j = -1;
	new_str = ft_calloc(sizeof (char *), ft_strlen(new_var) + 3);
	while (new_var[++j] && new_var[j - 1] != '=')
		new_str[++pos] = new_var[j];
	if (new_str[pos++] == '=')
	{
		new_str[pos] = DQ;
		while (new_var[j])
			new_str[++pos] = new_var[j++];
		new_str[++pos] = DQ;
	}
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
	while (shell->envp[++i])
	{
		if (!ft_strncmp(shell->envp[i], new_var, len))
		{
			shell->envp[i] = create_var(new_var, shell->envp[i]);
			collect_garbage(shell, shell->envp[i], 0);
		}
	}
}

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
		collect_garbage(shell, shell->envp[i], 0);
		//shell->envp[++i] = 0;
	}
	return (0);
}

int	pick_old_var(char *s)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	if (!s)
		return (0);
	while (s[++i] && s[i] != '=')
		;
	while (s[++i])
		len++;
	len -= 2;
	return (len);
}

char	*create_plus_var(char *new_var, char *new_str)
{
	int		j;
	int		pos;
	int		i;
	int		len;
	char	*old;

	pos = -1;
	j = -1;
	i = -1;
	old = new_str;
	len = pick_old_var(new_str);
	new_str = ft_calloc(sizeof (char *), (ft_strlen(new_var) - 1) + len + 3);
	while (new_var[++j] && new_var[j - 1] != '=')
	{
		if (new_var[j] == '+')
			j += 1;
		new_str[++pos] = new_var[j];
	}
	if (new_str[pos++] == '=')
	{
		new_str[pos] = DQ;
		if (old)
		{
			while (old[++i] && old[i] != DQ)
				;
			while (old[++i] && old[i] != DQ)
				new_str[++pos] = old[i];
		}
		while (new_var[j])
			new_str[++pos] = new_var[j++];
		new_str[++pos] = DQ;
	}
	return (new_str);
}

void	add_var(char *new_var, t_shell *shell)
{
	int	i;
	int	len;

	i = -1;
	len = -1;
	while (new_var[++len] && new_var[len] != '=' && new_var[len] != '+')
		;
	while (shell->envp[++i])
	{
		if (!ft_strncmp(shell->envp[i], new_var, len))
		{
			shell->envp[i] = create_plus_var(new_var, shell->envp[i]);
			collect_garbage(shell, shell->envp[i], 0);
		}
	}
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
		collect_garbage(shell, shell->envp[i], 0);
		//shell->envp[++i] = '\0';
	}
	return (0);
}

int	ft_export(char **export_mat, t_shell *shell)
{
	int	i;
	int	pos;
	int	flag;

	i = -1;
	pos = -1;
	if (export_mat[0])
	{
		if (matrix_len(export_mat) < 2)
		{
			while (shell->envp[++i])//stampare le virgolette per ogni env variable
				printf("declare -x %s\n", shell->envp[i]);
			return (0);
		}
		else
		{
			i = 0;
			while (export_mat[++i])
			{
				flag = 0;
				while (export_mat[i][++pos] && export_mat[i][pos] != '=')
				{
					if (export_mat[i][pos] == '+' && export_mat[i][pos + 1] == '=')
						flag = 1;
					else if (!ft_isalpha(export_mat[i][pos]) && export_mat[i][pos] != US
						&& !ft_isdigit(export_mat[i][0]))
					{
						printf("minishell: export: `%s': not a valid identifier\n", export_mat[i]);
						return (1);
					}
				}
				if (flag == 1)
					join_env(export_mat[i], shell);
				else if (flag == 0)
					ft_addtoenv(export_mat[i], shell);
			}
			return (0);
		}
	}
	return (1);
}
