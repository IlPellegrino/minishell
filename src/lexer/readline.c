/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:55 by nromito           #+#    #+#             */
/*   Updated: 2024/05/07 13:50:51 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_cmd(t_shell *shell, char *cmd)
{
	int		i;

	i = -1;
	while (shell->path_env[++i])
	{
		shell->cmd_name = ft_strjoin(shell->path_env[i], cmd);
		if (access_p(shell->cmd_name, X_OK) == 0)
			return (1);
	}
	return (0);
}

char *lexer(t_shell *shell)
{
	int		i;
	int		words;
	int		pipe_nbr;
	char	**tmp_input;
	t_token	token;

	i = -1;
	pipe_nbr = 0;
	tmp_input = shell->mat_input;
	words = count_words(shell);
	token.index = ft_calloc(sizeof (char), words + 1);
	if (!token.index)
		return (0);
	checker(shell, &token, words);
	while (tmp_input[++i])
	{
		if (tmp_input[i][0] == '|')
			pipe_nbr++;
	}
	i = -1;
	while (shell->mat_input[++i])
	{
		if (pipe_nbr > 0)
			//pipex();
			printf("culo\n");
		else
			forker(shell, shell->mat_input[i]);
	}
	//tokenizer(tokens);
	return (0);
}

void	forker(t_shell *shell, char *input_args)
{
	pid_t	pid;
	char **mat_cmd = ft_split(input_args, 32);
	pid = fork_p();
	if (pid == 0)
	{
		if (find_cmd(shell, input_args))
			execve_p(shell->cmd_name, mat_cmd, shell->envp);
	}
	else
		waitpid(pid, 0, 0);
}
