/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:29:02 by dukim             #+#    #+#             */
/*   Updated: 2024/02/29 02:09:14 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = 0;
	while (src[src_len] != '\0' && src_len + 1 < size)
	{
		dst[src_len] = src[src_len];
		src_len++;
	}
	if (size > 0)
		dst[src_len] = '\0';
	while (src[src_len] != '\0')
		src_len++;
	return (src_len);
}
