/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:56:16 by dukim             #+#    #+#             */
/*   Updated: 2024/03/04 13:55:32 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*convert_dest;
	unsigned char	*convert_src;
	size_t			size;

	if (dest == src)
		return (dest);
	if ((size_t)(dest - src) >= n)
		return (ft_memcpy(dest, src, n));
	convert_dest = (unsigned char *)dest;
	convert_src = (unsigned char *)src;
	size = n;
	while (--size > 0)
		convert_dest[size] = convert_src[size];
	*convert_dest = *convert_src;
	return ((void *)convert_dest);
}
