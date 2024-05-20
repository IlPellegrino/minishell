/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:38 by nromito           #+#    #+#             */
/*   Updated: 2024/05/20 12:08:03 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//echo "$USER ciao come stai" | ls | cat
// $USER si salva in str, poi si usa un altra stringa per scorrere input
// e quando trova $ fa il replace di user con nromito, dopo aver mallocato 
// per Input  - var. ambiente + 1($) + strlen di result; 

char	*create_new_var(t_shell *shell, char *input, int n)
{
	int		k;
	char	*result;
	char	*env_var;

	k = -1;
	env_var = ft_calloc(sizeof (char *), ft_strlen(input));
	while (input[++n] != SPACE && input[n] != '>'
		&& input[n] != PIPE && input[n] != '<'
		&& input[n] != '$' && input[n] != DQ
		&& input[n] != SQ && input[n])
		env_var[++k] = input[n];
	result = getenv(env_var);
	collect_garbage(shell, env_var, 0);
	if (result == NULL)
		return (0);
	return (result);
}

void	recreate_str(t_token *token, int j, char *input, char *new_var)
{
	int		n;
	int		k;
	char	*old_str;

	n = 0;
	k = 0;
	old_str = input;
	while (n < j)
		token->index[token->wrd][k++] = old_str[n++];
	n = 0;
	printf("new_var = %s\n", new_var);
	while (new_var[n])
		token->index[token->wrd][k++] = new_var[n++];
	while (old_str[++j] != SPACE && old_str[j] != '>'
		&& old_str[j] != PIPE && old_str[j] != '<'
		&& old_str[j] != $ && old_str[j] != SQ
		&& old_str[j] != DQ && old_str[j])
		;
	while (old_str[j])
		token->index[token->wrd][k++] = old_str[j++];
}

void	expand_value(t_shell *shell, t_token *token)
{
	int		j;
	char	*input;
	char	*new_var;

	j = -1;
	input = token->index[token->wrd];
	while (input[++j])
	{
		if (input[j] == SQ)
			while (input[++j] != SQ)
				;
		else if (input[j] == '$')
		{
			new_var = create_new_var(shell, input, j);
			if (!new_var)
				return ;
			collect_garbage(shell, token->index[token->wrd], 0);
			token->index[token->wrd] =
				ft_calloc(sizeof (char *), ft_strlen(input) + ft_strlen(new_var));
			if (!token->index[token->wrd])
				return ;
			recreate_str(token, j, input, new_var);
			input = token->index[token->wrd];
		}
	}
}

int	count_quotes(t_token *token)
{
	int 	i;
	int		quote_nbr;
	
	i = 0;
	quote_nbr = 0;
	while (token->index[token->wrd][i++])
	{
		if (token->index[token->wrd][i] == SQ)
		{
			while(token->index[token->wrd][++i]
				&& token->index[token->wrd][i] != SQ)
				;
			quote_nbr += 2;
		}
		else if (token->index[token->wrd][i] == DQ)
		{
			while(token->index[token->wrd][++i]
				&& token->index[token->wrd][i] != DQ)
				;
			quote_nbr += 2;
		}
	}
	return (i - quote_nbr);
}

char	*remove_quotes(t_shell *shell, t_token *token, int i)
{
	int		j;
	char*	temp;

	j = 0;
	temp = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while(token->index[token->wrd][++i])
	{
		if (token->index[token->wrd][i] == SQ)
			while(token->index[token->wrd][++i]
				&& token->index[token->wrd][i] != SQ)
				temp[j++] = token->index[token->wrd][i];
		else if (token->index[token->wrd][i] == DQ)
			while(token->index[token->wrd][++i]
				&& token->index[token->wrd][i] != DQ)
				temp[j++] = token->index[token->wrd][i];
		else if (token->index[token->wrd][i])
			temp[j++] = token->index[token->wrd][i];
	}
	collect_garbage(shell, token->index[token->wrd], 0);
	return (temp);
}

// void	expander(t_shell *shell, t_token *token)
// {
// 	int		n;
// 	char	**tmp;

// 	token->exp = -1;
// 	while (++token->exp < token->wrd)
// 	{
// 		n = -1;
// 		tmp = token->index;
// 		while (tmp[token->exp][++n])
// 			if (tmp[token->exp][n] == '$')
// 				expand_value(shell, token);
// 	}
// }

// char	*expand_value(char *fake, int *j)
// {
// 	char	*result;
// 	int		i;
// 	char	*env_var;

// 	i = 0;
// 	env_var = ft_calloc(sizeof (char *), 5);
// 	(*j) += 1;
// 	while (fake[(*j)] != SPACE && fake[(*j)] != '>' && fake[(*j)] != '$'
// 		&& fake[(*j)] != PIPE && fake[(*j)] != '<' && fake[(*j)] != '\0')
// 	// while (fake[++j] != '_' && (fake[j] < '0' && fake[j] > '9') 
// 	// 	&& (fake[j] < 'a' && fake[j] > 'z') 
// 	// 	&& (fake[j] < 'A' && fake[j] > 'Z'))
// 	{
// 			env_var[i] = fake[(*j)];
// 			(*j)++;
// 			i++;
// 	}
// 	env_var[i] = '\0';
// 	result = getenv(env_var);
// 	printf("RESULT = %s\n", result);
// 	if (result == NULL)
// 		return (0);
// 	return(result);
// }

// void	expander(t_shell *shell, t_token *token)
// {
// 	int		i;
// 	int		j;
// 	int		g;
// 	int		k;
// 	char*	fake;
// 	int		temp_len;
// 	char*	temp_res;
	
// 	g = 0;
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (i < token->wrd)
// 	{
// 		fake = token->index[i];
// 		while (fake[j])
// 		{
// 			if (fake[j] == '$')
// 			{
// 				k = j;
// 				temp_res = expand_value(fake, &j);
// 				temp_len = ft_strlen(temp_res);
// 				collect_garbage(shell, token->index[i], 0);
// 				token->index[i] = ft_calloc(sizeof (char *), k + temp_len);
// 				while (g < k)
// 				{
// 					token->index[i][g] = fake[g];
// 					g++;
// 				}
// 				k = 0;
// 				while (temp_res[k] != '\0')
// 				{
// 					token->index[i][g] = temp_res[k];
// 					k++;
// 					g++;
// 				}
// 			}
// 			else
// 			{
// 				j++;
// 				g = 0;
// 			}
// 		}
// 		g = 0;
// 		j = 0;
// 		i++;
// 	}
// }

