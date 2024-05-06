/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:46:29 by nromito           #+#    #+#             */
/*   Updated: 2024/05/06 23:33:42 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/minishell.h"

// checker for even/odd quotes

int	count_words(t_shell *shell)
{
	/*int	i;
	int	words;
	
	i = -1;
	words = 0;
	while (shell->input[i] == SPACE)
		i++;
	while (shell->input[++i] != '\0')
	{
		if (shell->input[i] == SPACE)
		{
			while (shell->input[i + 1] == SPACE && shell->input[i] != '\0')
				i++;
			if (shell->input[i] != 0)
				words++;
		}
		else if (shell->input[i] == DQ)
		{
			i++;
			while (shell->input[i] != DQ)
				i++;
		}
		else if (shell->input[i] == SQ)
		{
			i++;
			while (shell->input[i] != SQ)
				i++;
		}
		if (shell->input[i + 1] == '\0')
			words++;
	}*/
	int		i;
	int		j;
	int		words;
	char	*new_input;

	words = 0;
	j = 0;
	new_input = ft_calloc(sizeof(char*), ft_strlen(shell->input));
	if (!new_input)
		return (0);
	i = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == DQ)
		{
			while (shell->input[i] == DQ)
				i++;
			while (shell->input[i] != DQ)
			{
				if (shell->input[i] == 32)
					new_input[j] = '_';
				else
					new_input[j] = shell->input[i];
				i++;
				j++;
			}
			while (shell->input[i] == DQ)
				i++;
		}
		else if (shell->input[i] == SQ)
		{
			while(shell->input[i] == SQ)
				i++;
			while (shell->input[i] != SQ)
			{
				if (shell->input[i] == 32)
					new_input[j] = '_';
				else
					new_input[j] = shell->input[i];
				i++;
				j++;
			}
			while (shell->input[i] == SQ)
				i++;
		}
		else
			new_input[j++] = shell->input[i++];
	}
	printf("new input = %s\n", new_input); 
	i = 0;
	while (new_input[i] == SPACE)
		i++;
	while (new_input[i])
	{
		while (new_input[i] == SPACE)
			i++;
		if (new_input[i])
			words++;
		while (new_input[i] != SPACE && new_input[i])
			i++;
	}
	printf("%d\n", words);
	return (words);
}


int	find_SQ(t_shell *shell, int	i)
{
	while (shell->input[i] != SQ && shell->input[i] != '\0')
		i++;
	if (shell->input[i] == '\0')
		ft_error(NULL, 40);
	else if (shell->input[i] == SQ)
		return (i);
	return (0);
}

int	find_DQ(t_shell *shell, int	i)
{
	while (shell->input[i] != DQ && shell->input[i] != '\0')
		i++;
	if (shell->input[i] == '\0')
		ft_error(NULL, 40);
	else if (shell->input[i] == DQ)
		return (i);
	return (0);
}

// needs to be checked and finished, just made the first part of it.
void	checker(t_shell *shell, t_token *token, int words)
{
	int		i;
	int		j;
	int		k;
	int		r;
	int		l;
	
	r = 0;
	k = 0;
	i = 0;
	j = 0;
	l = 0;
	while (shell->input[i] == 32)
		i++;
	l = i;
	while (j <= words)
	{
//		printf("words = %d\n", words);
//		printf("I e' = %d\n", i);
//		printf("L e' = %d\n", l);
		if (shell->input[i] == SQ)
		{
			k = find_SQ(shell, i);
			while (i < k)
				i++;
				// token->index[j][r] = shell->input[i];
		}
		else if (shell->input[i] == DQ)
		{
			k = find_DQ(shell, i);
			while (i < k)
				i++;
				// token->index[j][r++] = shell->input[i];
		}
		else if ((shell->input[i] == SPACE ) || (shell->input[i] == '\0'))
		{
//			printf("entrato\n");
			token->index[j] = ft_calloc(sizeof (char), (i - l + 1));
			while (l < i)
			{
				if (shell->input[l] == DQ)
					while (shell->input[l] != DQ)
						token->index[j][r++] = shell->input[l++];
				else if (shell->input[l] == SQ)
					while (shell->input[l] != SQ)
						token->index[j][r++] = shell->input[l++];
				else
					token->index[j][r++] = shell->input[l++];
			}
			token->index[j][r++] = '\0';
			j++;
			while (shell->input[i] == SPACE && shell->input[i] != '\0')
				i++;
			if (shell->input[i] != '\0')
				l = i;
		}
		else
			i++;
	}
	print_matrix(token->index);
}
