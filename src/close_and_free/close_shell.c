/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:32:57 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/10 11:35:22 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_list(t_garbage *col)
{
	printf("---this is the garbage---");
	while (col)
	{
	
		printf("arg = %s mat = %s", (char*)col->arg, (char*)col->mat[0]);
		col = col->next;
	}
}

t_garbage *new_node(char *arg, char **mat)
{
	t_garbage *node;
	
	node = malloc(sizeof(t_garbage));
	if (!node)
		return (0);
	if (arg)
		node->arg = arg;
	else
		node->mat = mat;
	node->next = NULL;
	return (node);
}

int	collect_garbage(t_shell *shell, char *arg, char **mat)
{
	t_garbage *collect;
	
	collect = shell->collector;
	while (collect->next)
		collect = collect->next;
	//printf("start collecting\n");
	collect->next = new_node(arg, mat);
	//printf("collected the arg = %s\n", (char*)collect->arg);
	//printf("collected!\n");
	return (1);
}
void	close_shell(t_shell *shell)
{
	t_garbage *garbage;
	t_garbage *temp;

	garbage = shell->collector;
	temp = garbage->next;
	free(garbage);
	garbage = NULL;
	garbage = temp;
	while (garbage)
	{
		if (garbage->arg)
			free(garbage->arg);
		else if (garbage->mat)
			free_matrix((char**)garbage->mat);
		temp = garbage->next;
		free(garbage);
		garbage = temp;
	}
	//printf("%d\n", errno);
	exit(errno);
}
