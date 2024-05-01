/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:58:12 by nromito           #+#    #+#             */
/*   Updated: 2024/04/30 16:26:32 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **matrix, int r)
{
	while (--r >= 0)
		free (matrix[r]);
	free(matrix);
	return (NULL);
}

char	**fill_matrix(char **matrix, int words, const char *s, const char c)
{
	int	r;
	int	len;
	int	i;

	r = 0;
	len = 0;
	i = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		len = 0;
		if (*s == 39) //apici
		{
			s++;
			while (s[len] != 39 && s[len] != 0)
				len++;
			if (len == 0)
				s++;
			else if (*s == '/0') //heredoc
			{}
			else
			{
				matrix[r] = malloc (sizeof(char) * (len + 1));
				if (matrix[r] == NULL)
					return (free_all(matrix, r));
				matrix[r][len++] = '\0';
				i = len - 1;
				while (--len > 0)
					matrix[r][len - 1] = s[len - 1];
				s += i;
				r++;
			}
		}
		else if (*s == 34) //virgolette
		{
			s++;
			while (s[len] != 34 && s[len] != 0)
				len++;
			if (len == 0)
				s++;
			else if (*s == '/0') //heredoc
			{}
			else
			{
				matrix[r] = malloc (sizeof(char) * (len + 1));
				if (matrix[r] == NULL)
					return (free_all(matrix, r));
				matrix[r][len++] = '\0';
				i = len - 1;
				while (--len > 0)
					matrix[r][len - 1] = s[len - 1];
				s += i;
				r++;
			}
		}
		else //solo spazi
		{
			while (s[len] != c && s[len] != 0 && s[len] != 34 && s[len] != 39)
				len++;
			matrix[r] = malloc (sizeof(char) * (len + 1));
			if (matrix[r] == NULL)
				return (free_all(matrix, r));
			matrix[r][len++] = '\0';
			i = len - 1;
			while (--len > 0)
				matrix[r][len - 1] = s[len - 1];
			s += i;
			r++;
		}		
	}
	return (matrix);
}

char	**ft_split(char const *s, char const c)
{
	int		i;
	int		j;
	int		words;
	char	**matrix;

	if (s == NULL || *s == '\0')
	{
		matrix = ft_calloc(sizeof(char *), 1);
		if (matrix == NULL)
			return (NULL);
		return (matrix);
	}
	i = 0;
	words = 0;
	while (s[i + 1] != 0 && s[i + 1] == c)
		i++;
	while (s[i] != 0)
	{
		j = 0;
		if (s[i] == 34)
		{
			i++;
			while (s[i] != 34)
				j++;
			if (j > 0)
				words++;
			i += j;
		}
		else if (s[i] == 39)
		{
			i++;
			while (s[i] != 39)
				j++;
			if (j > 0)
				words++;
			i += j;
		}
		else
		{
			while (s[i] != 0 && s[i] != c && s[i] != 34 && s[i] != 39)
				j++;
			if (j > 0)
				words++;
			i += j;
		}
		i++;
	}
	matrix = malloc(sizeof(char *) * (words + 1));
	if (!matrix)
		return (NULL);
	matrix[words] = NULL;
	return (fill_matrix(matrix, words, s, c));
}
