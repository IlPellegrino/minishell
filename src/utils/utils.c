/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:59:43 by nromito           #+#    #+#             */
/*   Updated: 2024/06/12 12:31:16 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	init_structs(t_shell *shell, int argc, char **argv, char **envp)
{
	t_token		*token;
	t_garbage	*garbage;

	(void)argc;
	(void)argv;
	shell->error = 0;
	shell->len = 0;
	shell->envp = ft_matrix_dup(envp);
	if (!shell->envp)
		return (0);
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
	shell->executor = 0;
	collect_garbage(shell, 0, shell->envp);
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

int	check_exit_status(int error_type)
{
	int	error;

	error = 0;
	if (error_type == COMMAND)
		error = 127;
	else if (error_type == ENV)
		error = 127;
	else if (error_type == UNSET)
		error = 1;
	else if (error_type == EXPORT)
		error = 1;
	else if (error_type == SYNTAX)
		error = 2;
	else if (error_type == EXIT)
		error = 2;
	else if (error_type == OPEN_ERR)
		error = 1;
	else if (error_type == CD_DIR)
		error = 1;
	else if (error_type == CD_ARGS)
		error = 1;
	return (error);
}

void	print_err(char *str, char *var, char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd(str2, 2);
}

int	ft_error(t_shell *shell, int error_type, char *str)
{
	if (error_type == COMMAND)
		print_err("", str, ": command not found");
	else if (error_type == ENV)
		print_err("env: `", str, "': No such file or directory");
	else if (error_type == EXIT)
		print_err("minishell: exit: ", str, ": numeric argument required");
	else if (error_type == UNSET)
		print_err("minishell: unset: `", str, "': not a valid identifier");
	else if (error_type == EXPORT)
		print_err("minishell: export: `", str, "': not a valid identifier");
	else if (error_type == SYNTAX)
		print_err("minishell: syntax error near unexpected token '", str, "'");
	else if (error_type == OPEN_ERR)
		print_err("minishell: ", str, ": No such file or directory");
	else if (error_type == HERE_EOF)
		ft_putendl_fd(EOF_ERROR, 2);
	else if (error_type == CD_DIR)
		print_err("minishell: cd: ", str, ": No such file or directory");
	else if (error_type == CD_ARGS)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	shell->error = check_exit_status(error_type);
	return (0);
}
