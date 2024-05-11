/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:54:36 by nromito           #+#    #+#             */
/*   Updated: 2024/05/11 16:48:34 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


void	free_matrix(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
}

int	get_path(t_shell *shell)
{
	char 	*path;
	char	*temp;
	int		i = -1;

	path = getenv("PATH");
	shell->path_env = ft_split(path, ':');
	if (!shell->path_env)
		return (0);
	temp = ft_strdup(shell->path_env[0]);
	free(shell->path_env[0]);
	shell->path_env[0] = ft_strtrim(temp, "PATH="); // crea la path da passare all'access
	free(temp);
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
		printf("after [%c]\n", token->tokens[i + 1]);
		if (is_redir(token->tokens[i]) && find_space(token->index[i]))
			return (ft_error(COMMAND, token->index[i]));		
		else if (token->tokens[i] == 'h')
		{
			if (token->tokens[i + 1] == 'P')
				return (ft_error(PARSE, token->index[i + 1]));
			else if (!*++token->tokens)
			{
				printf("parse error null\n");
				return (ft_error(PARSE, "\\n"));
			}
		}
	}
	return (1);
}

int	parsing(t_shell *shell)
{
	char *str = getenv("USER");
	printf("user = %s\n", str);
	if (!tokenizer(shell))
		return (ft_error(COMMAND, "<< "));
	return (parse_input(shell));
	//init_cmd_table(shell);
	return (1);
}
