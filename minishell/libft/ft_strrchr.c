/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:11:55 by dukim             #+#    #+#             */
/*   Updated: 2024/02/29 02:18:36 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*temp;

	while (c > 256)
		c -= 256;
	temp = (char *)s;
	len = ft_strlen(temp) - 1;
	if (c == 0)
		return (temp + len + 1);
	while (len >= 0)
	{
		if (temp[len] == c)
			return (temp + len);
		len--;
	}
	return (0);
}
