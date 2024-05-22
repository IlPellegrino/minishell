/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:29:28 by nromito           #+#    #+#             */
/*   Updated: 2024/05/21 14:58:36 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*recursive(long long i, long long j, char *digit)
{
	if (i < 0)
	{
		i = -i;
		digit[0] = '-';
	}
	if (i > 0)
	{
		digit[--j] = 48 + (i % 10);
		recursive((i / 10), j, digit);
	}
	return (digit);
}

int	count_num(long long n)
{
	short	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*digit;
	long long	nb;
	long long	j;

	nb = n;
	j = count_num(nb);
	digit = malloc(sizeof(char) * (j + 1));
	if (digit == NULL)
		return (NULL);
	if (nb < 0)
	{
		nb = -nb;
		digit[0] = '-';
	}
	digit = recursive(nb, j, digit);
	digit[j] = '\0';
	return (digit);
}
