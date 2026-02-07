/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:55:46 by dukim             #+#    #+#             */
/*   Updated: 2024/03/08 18:58:30 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			len;
	unsigned char	*us1;
	unsigned char	*us2;

	len = 0;
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while ((us1[len] != '\0' && us2[len] != '\0') && len < n)
	{
		if (us1[len] != us2[len])
			return (us1[len] - us2[len]);
		len++;
	}
	if (len == n)
		return (0);
	return (us1[len] - us2[len]);
}
