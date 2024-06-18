/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:59:43 by nromito           #+#    #+#             */
/*   Updated: 2024/06/17 17:36:31 by ciusca           ###   ########.fr       */
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

int	check_exit_status(t_shell *shell, int error_type)
{
	if (error_type == ENV || error_type == NO_FILE
		|| error_type == COMMAND)
		shell->error = 127;
	else if (error_type == UNSET || error_type == CD_UNSET)
		shell->error = 1;
	else if (error_type == EXPORT)
		shell->error = 1;
	else if (error_type == SYNTAX)
		shell->error = 2;
	else if (error_type == EXIT)
		shell->error = 2;
	else if (error_type == OPEN_ERR)
		shell->error = 1;
	else if (error_type == CD_DIR)
		shell->error = 1;
	else if (error_type == CD_ARGS)
		shell->error = 1;
	else if (error_type == BINARY)
		shell->error = 2;
	else if (error_type == FOLDER || error_type == NOT_FOLDER
		|| error_type == NO_PERMISSION)
		shell->error = 126;
	return (0);
}

void	print_err(char *str, char *var, char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd(str2, 2);
}

int	ft_error2(int error_type, char *str)
{
	if (error_type == FOLDER)
		print_err("minishell: ", str, ": Is a directory");
	else if (error_type == NOT_FOLDER)
		print_err("minishell: ", str, ": Not a directory");
	else if (error_type == NO_FILE)
		print_err("minishell: ", str, ": No such file or directory");
	else if (error_type == NO_PERMISSION)
		print_err("minishell: ", str, ": Permission denied");
	else if (error_type == CD_UNSET)
		print_err("minishell: cd: ", str, " not set");
	return (1);
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
		print_err("minishell: syntax error near unexpected token `", str, "'");
	else if (error_type == OPEN_ERR)
		print_err("minishell: ", str, ": No such file or directory");
	else if (error_type == HERE_EOF)
		ft_putendl_fd(EOF_ERROR, 2);
	else if (error_type == CD_DIR)
		print_err("minishell: cd: ", str, ": No such file or directory");
	else if (error_type == CD_ARGS)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else if (error_type == BINARY)
		ft_putendl_fd("cannot execute non binary files", 2);
	else
		ft_error2(error_type, str);
	return (check_exit_status(shell, error_type));
}
