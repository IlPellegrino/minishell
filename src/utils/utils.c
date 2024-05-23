/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:59:43 by nromito           #+#    #+#             */
/*   Updated: 2024/05/23 15:11:18 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_space(char *index)
{
	int	i;

	i = 0;
	while (index[i] != SPACE)
		i++;
	printf("index[i] = %c\n", index[i]);
	if (!index[i])
		return (0);
	return (1);
}

int	init_structs(t_shell *shell, int argc, char **argv, char **envp)
{
	t_token		*token;
	t_garbage	*garbage;

	(void)argc;
	(void)argv;
	shell->error = 0;
	shell->envp = envp;
	token = malloc(sizeof(t_token));
	shell->tokens = token;
	garbage = malloc(sizeof(t_garbage));
	garbage->next = NULL;
	garbage->arg = 0;
	garbage->mat = 0;
	shell->len = 0;
	shell->collector = garbage;
	shell->cmd_table = 0;
	shell->arrow = ft_calloc(sizeof(char *), ft_strlen(GREEN_ARROW) + 1);
	collect_garbage(shell, shell->arrow, 0);
	shell->arrow = GREEN_ARROW;
	return (1);
}

void	print_matrix(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		printf("[%s]\n", mat[i]);
		i++;
	}
}

int	ft_error(t_shell *shell, int error_type, char *str)
{
	if (error_type == COMMAND)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd("[", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("]", 2);
		shell->error = 127;
	}
	else if (error_type == SYNTAX)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("'", 2);
		shell->error = 2;
	}
	else if (error_type == OPEN_ERR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("No such file or directory", 2);
		shell->error = 1;
	}
	return (0);
}
