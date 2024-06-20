/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/06/18 16:07:11 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_sig_type;

void	set_arrow(t_shell *shell)
{
	if (!shell->error)
		shell->arrow = GREEN_ARROW;
	else
		shell->arrow = RED_ARROW;
	printf("%s", shell->arrow);
}

char	*ft_readline(char *str)
{
	char	*input;

	if (isatty(fileno(stdin)))
		input = readline(str);
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		input = ft_strtrim(line, "\n");
		free(line);
	}
	if (!input)
		return (0);
	add_history(input);
	rl_on_new_line();
	return (input);
}

int	handle_close(t_shell *shell, int saved_in)
{
	dup2(saved_in, STDIN_FILENO);
	close(saved_in);
	if (g_sig_type != SIG_C)
	{
		//ft_putendl_fd("exit", 2);
		close_shell(shell);
	}
	else if (g_sig_type == SIG_C)
		shell->error = 130;
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	int			saved_in;

	init_structs(&shell, argc, argv, envp);
	while (JESUS)
	{
		saved_in = dup(STDIN_FILENO);
		g_sig_type = 0;
		get_signal();
		//set_arrow(&shell);
		shell.input = ft_readline(MINISHELL);
		if (!shell.input)
			handle_close(&shell, saved_in);
		close(saved_in);
		get_path(&shell);
		if (shell.input)
		{
			if (lexer(&shell) && parsing(&shell) && executor(&shell))
				shell.error = 0;
			free(shell.input);
			if (shell.cmd_table)
				free_cmd_table(&shell);
			delete_heredoc();
		}
	}
}
