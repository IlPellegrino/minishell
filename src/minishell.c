/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:26:12 by nromito           #+#    #+#             */
/*   Updated: 2024/07/03 12:23:19 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_sig_type;

int	check_sign(const char *str, int *i, int *is_neg)
{
	int	neg;

	neg = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[(*i)++] == '-')
		{
			*is_neg = 1;
			neg *= -1;
		}
	}
	return (neg);
}

char	*set_prompt(t_shell *shell)
{
	char	*dir;
	char	*prompt;
	char	*temp;

	temp = getcwd(0, 0);
	dir = ft_strdup(ft_strrchr(temp, '/'));
	free(temp);
	if (!shell->error)
	{
		temp = ft_strjoin(dir, RESET SECOND_PART);
		free(dir);
		prompt = ft_strjoin(MINISHELL, temp);
		free(temp);
		collect_garbage(shell, prompt, 0);
		return (prompt);
	}
	temp = ft_strjoin(dir, RESET SECOND_RED);
	free(dir);
	prompt = ft_strjoin(RED_MINISHELL, temp);
	free(temp);
	collect_garbage(shell, prompt, 0);
	return (prompt);
}

char	*ft_readline(char *str)
{
	char	*input;

	input = readline(str);
	if (!input)
		return (0);
	rl_on_new_line();
	return (input);
}

int	handle_close(t_shell *shell, int saved_in)
{
	if (!shell->input)
	{
		close(saved_in);
		close_shell(shell);
	}
	else if (g_sig_type == 3)
	{
		shell->error = 130;
		g_sig_type = 0;
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
		return (0);
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
		get_signal();
		saved_in = dup(STDIN_FILENO);
		shell.input = ft_readline(set_prompt(&shell));
		handle_close(&shell, saved_in);
		if (!parse_open(&shell))
			continue ;
		update_history(shell.input);
		collect_garbage(&shell, shell.input, 0);
		close(saved_in);
		if (shell.input)
		{
			if (lexer(&shell) && parsing(&shell, saved_in) && executor(&shell))
				shell.error = 0;
			if (shell.cmd_table)
				free_cmd_table(&shell);
		}
		delete_heredoc();
	}
}
