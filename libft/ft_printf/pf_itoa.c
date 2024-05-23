/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:45:44 by ciusca            #+#    #+#             */
/*   Updated: 2024/02/17 19:08:45 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	nb_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i ++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i ++;
	}
	return (i);
}

int	pf_itoa(long cifra)
{
	char	*str;
	int		len;
	int		count;

	count = 0;
	len = nb_len(cifra) -1;
	str = (char *) malloc(sizeof(char) * len + 2);
	if (!str)
		return (0);
	if (cifra < 0)
	{
		cifra *= -1;
		str[0] = '-';
	}
	if (cifra == 0)
		str[0] = '0';
	str[len + 1] = 0;
	while (cifra > 0)
	{
		str[len--] = cifra % 10 + 48;
		cifra /= 10;
	}
	count += pf_putstr(str);
	free(str);
	return (count);
}
