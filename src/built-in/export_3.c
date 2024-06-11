/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:10:38 by nromito           #+#    #+#             */
/*   Updated: 2024/06/11 10:31:56 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*create_plus_var(char *new_var, char *new_str)
{
	int			len;
	t_export	export;

	export.pos = -1;
	export.old_pos = -1;
	export.old = new_str;
	len = pick_old_var(new_str);
	new_str = ft_calloc(sizeof (char *), ft_strlen(new_var) + len + 1);
	while (new_var[++export.old_pos] && new_var[export.old_pos] != '+')
		new_str[++export.pos] = new_var[export.old_pos];
	if (new_var[export.old_pos++] == '+')
		new_str = write_inside(new_str, new_var, &export);
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
		if (len == count_len(shell->envp[i]))
		{
			if (!ft_strncmp(shell->envp[i], new_var, len))
			{
				shell->envp[i] = create_plus_var(new_var, shell->envp[i]);
				collect_garbage(shell, shell->envp[i], 0);
			}
		}
	}
	shell->envp[i] = NULL;
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

char	*write_inside(char *result, char *new_var, t_export *export)
{
	int	i;

	i = -1;
	if (new_var[export->old_pos] == '=')
		result[++export->pos] = new_var[export->old_pos];
	if (export->old)
	{
		while (export->old[++i] && export->old[i] != '=')
			;
		while (export->old[++i])
			result[++export->pos] = export->old[i];
	}
	while (new_var[++export->old_pos])
		result[++export->pos] = new_var[export->old_pos];
	return (result);
}
