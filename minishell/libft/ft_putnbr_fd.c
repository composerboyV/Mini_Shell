/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:59:04 by dukim             #+#    #+#             */
/*   Updated: 2024/03/06 20:05:02 by dukim            ###   ########.fr       */
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

void	ft_putnbr_fd(int n, int fd)
{
	char				nbr[12];
	unsigned int		pow;
	unsigned int		un;
	int					i;

	i = 0;
	if (n < 0)
	{
		un = -n;
		nbr[i++] = '-';
	}
	else
		un = n;
	pow = pow_ten(un);
	while (pow)
	{
		nbr[i++] = (un / pow) + '0';
		un = un % pow;
		pow /= 10;
	}
	nbr[i] = '\0';
	if (i == 0)
		ft_putstr_fd("0", fd);
	else
		ft_putstr_fd(nbr, fd);
}
