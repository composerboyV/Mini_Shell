/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:29:25 by dukim             #+#    #+#             */
/*   Updated: 2024/03/04 13:28:06 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;

	if (size != 0 && nmemb > 2147483637 / size)
		return (0);
	memory = malloc(nmemb * size);
	if (!memory)
		return (0);
	memory = ft_memset(memory, 0, size * nmemb);
	return (memory);
}
