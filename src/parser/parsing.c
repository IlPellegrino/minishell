/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:54:36 by nromito           #+#    #+#             */
/*   Updated: 2024/05/20 13:01:45 by nromito          ###   ########.fr       */
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

char	*remove_redir(t_token *token)
{
	int		i;
	char	*temp_token;

	temp_token = ft_strdup(token->tokens);
	i = -1;
	while (token->tokens[++i])
		if (is_redir(token->tokens[i]) || is_redir(token->tokens[i - 1]))
			temp_token[i] = 'X';
	return (temp_token);
}

int	get_path(t_shell *shell)
{
	char 	*path;
	char	*temp;
	int		i;
	
	i = -1;
	path = getenv("PATH");
	shell->path_env = ft_split(path, ':');
	if (!shell->path_env)
		return (0);
	while (shell->path_env[++i])
	{
		temp = ft_strdup(shell->path_env[i]);
		free(shell->path_env[i]);
		shell->path_env[i] = ft_strjoin(temp, "/");  // add "/" for access function
		free(temp);
	}
	collect_garbage(shell, 0, shell->path_env);
	return (1);
}

int	parse_command(t_shell *shell)
{
	t_token	*token;
	int		i;
	// int		counter;
	// int		j;

	// j = 0;
	// counter = 0;
	token = shell->tokens;
	token->temp_token = remove_redir(token);
	collect_garbage(shell, token->temp_token, 0);
	i = -1;
	while (token->temp_token[i] == 'X')
		i++;
	if (token->temp_token[i] != 'C' && token->temp_token[i])
		return (ft_error(COMMAND, token->index[i]));
	//printf("temp token = %s\n", temp_token);
	return (1);
}

int	parse_input(t_shell *shell)
{
	t_token *token;
	int		i;
	
	token = shell->tokens;
	i = -1;
	if (token->tokens[0] == 'S')
		return (ft_error(COMMAND, token->index[0]));
	while (token->tokens[++i])
	{		
		if (is_redir(token->tokens[i]))
		{
			if (token->tokens[i + 1] == 'P')
				return (ft_error(SYNTAX, token->index[i + 1]));
			else if (!token->tokens[i + 1])
				return (ft_error(SYNTAX, "\\n"));
			//if (is_redir(token->tokens[i + 1]) && !is_quoted[i])
				//return (ft_error(SYNTAX), token->tokens[i + 1]); 
		}
	}
	i = -1;
	return (parse_command(shell));
}

int	parsing(t_shell *shell)
{
	char *str = getenv("USER");
	printf("user = %s\n", str);
	if (!tokenizer(shell))
		return (ft_error(COMMAND, "<< "));
	if (!parse_input(shell))
		return (0);
	//if (!init_cmd_table(shell))
	//	return (0);
	return (1);
}
