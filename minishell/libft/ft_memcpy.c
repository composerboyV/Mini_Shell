/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:30:47 by dukim             #+#    #+#             */
/*   Updated: 2024/03/04 13:42:24 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*convert_dest;
	unsigned char	*convert_src;
	size_t			size;

	if (dest == src)
		return (dest);
	convert_dest = (unsigned char *)dest;
	convert_src = (unsigned char *)src;
	size = 0;
	while (size < n)
	{
		convert_dest[size] = convert_src[size];
		size++;
	}
	return (dest);
}
