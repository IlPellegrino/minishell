/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:59:43 by nromito           #+#    #+#             */
/*   Updated: 2024/05/11 16:39:39 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_redir(int c)
{
	if (c == 'H')
		return(1);
	else if (c == 'I')
		return (1);
	if (c == 'O')
		return(1);
	else if (c == 'A')
		return (1);
	return (0);
}

int	find_space(char *index)
{
	int	i;

	i = 0;
	while (index[i] != SPACE)
		i++;
	printf("index[i] = %c\n", index[i]);
	if (!index[i])
		return(0);
	return (1);
}

int	init_structs(t_shell *shell)
{
	t_token 	*token;
	t_garbage 	*garbage;

	token = malloc(sizeof(t_token));
	shell->tokens = token;
	garbage = malloc(sizeof(t_garbage));
	garbage->next = NULL;
	garbage->arg = 0;
	garbage->mat = 0;
	shell->collector = garbage;
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

int	ft_error(int error_type, char *str)
{
	if (error_type == COMMAND)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd("[", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("]", 2);
	}
	else if (error_type == PARSE)
	{
		ft_putstr_fd("minishell: parse error near '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("'", 2);
	}
	return (0);
}