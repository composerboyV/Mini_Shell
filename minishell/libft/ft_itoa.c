/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:24:49 by dukim             #+#    #+#             */
/*   Updated: 2024/03/06 17:55:51 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pow_ten(unsigned int un)
{
	unsigned int	pow;

	if (un >= 1000000000)
		return (1000000000);
	pow = 1;
	while (pow <= un)
		pow *= 10;
	return (pow / 10);
}

char	*ft_itoa(int n)
{
	char				itoa[12];
	unsigned int		pow;
	unsigned int		un;
	int					i;

	i = 0;
	if (n < 0)
	{
		un = -n;
		itoa[i++] = '-';
	}
	else
		un = n;
	pow = pow_ten(un);
	while (pow)
	{
		itoa[i++] = (un / pow) + '0';
		un = un % pow;
		pow /= 10;
	}
	itoa[i] = '\0';
	if (i == 0)
		return (ft_strdup("0"));
	return (ft_strdup(itoa));
}
