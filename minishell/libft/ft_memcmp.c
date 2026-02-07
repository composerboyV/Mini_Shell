/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:18:04 by dukim             #+#    #+#             */
/*   Updated: 2024/03/04 14:05:18 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*convert_s1;
	unsigned char	*convert_s2;
	size_t			size;

	convert_s1 = (unsigned char *)s1;
	convert_s2 = (unsigned char *)s2;
	size = 0;
	while (size < n)
	{
		if (convert_s1[size] != convert_s2[size])
			return (convert_s1[size] - convert_s2[size]);
		size++;
	}
	return (0);
}
