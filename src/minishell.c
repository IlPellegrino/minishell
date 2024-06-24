/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/06/24 02:57:56 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_sig_type;

char	*set_prompt(t_shell *shell)
{
	char	*dir;
	char	*prompt;
	char	*temp;

	temp = getcwd(0, 0);
	dir = ft_strrchr(temp, '/');
	free(temp);
	if (!shell->error)
	{
		temp = ft_strjoin(dir, RESET SECON_PART);
		//free(dir);
		prompt = ft_strjoin(MINISHELL, temp);
		free(temp);
		collect_garbage(shell, prompt, 0);
		return (prompt);
	}
	temp = ft_strjoin(dir, RESET SECOND_RED);
	//free(dir);
	prompt = ft_strjoin(RED_MINISHELL, temp);
	free(temp);
	collect_garbage(shell, prompt, 0);
	return (prompt);
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
	if (!shell->input)
	{
		close_shell(shell);
	}
	else if (g_sig_type == 19)
	{
		shell->error = 130;
		g_sig_type = 0;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	int			saved_in;

	init_structs(&shell, argc, argv, envp);
	g_sig_type = 0;
	while (JESUS)
	{
		saved_in = dup(STDIN_FILENO);
		get_signal();
		shell.input = ft_readline(set_prompt(&shell));
		handle_close(&shell, saved_in);
		collect_garbage(&shell, shell.input, 0);
		if (!parse_open(&shell))
			continue ;
		close(saved_in);
		get_path(&shell);
		if (shell.input)
		{
			if (lexer(&shell) && parsing(&shell) && executor(&shell))
				shell.error = 0;
			if (shell.cmd_table)
				free_cmd_table(&shell);
			delete_heredoc();
		}
		update_history(&shell);
	}
}
