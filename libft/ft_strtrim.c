/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:37:52 by nromito           #+#    #+#             */
/*   Updated: 2023/10/29 15:00:15 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	boolean(const char s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*trim;
	size_t	i;
	size_t	len;
	size_t	j;

	j = 0;
	i = 0;
	len = ft_strlen(s1) - 1;
	if (s1[i] == 0)
		return (ft_strdup(""));
	while (s1[i] && boolean(s1[i], set))
		i++;
	while (len > i && boolean(s1[len], set))
		len--;
	trim = malloc(sizeof(char) * (len - i) + 2);
	if (trim == NULL)
		return (NULL);
	while (i <= len)
	{
		trim[j] = s1[i];
		i++;
		j++;
	}
	trim[j] = '\0';
	return (trim);
}

// int main(void)
// {
//     const char *s1 = "\t\t\n\n\t   \t\n \t   He ";
//     const char *set = " \n\t";
//     char *result = ft_strtrim(s1, set);
//     printf("Trimmed string:%s\n", result);
//     free(result);
//     return 0;
// }