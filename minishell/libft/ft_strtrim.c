/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:56:10 by dukim             #+#    #+#             */
/*   Updated: 2024/03/15 14:51:28 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	left_trim;
	size_t	right_trim;

	if (!s1 || !set)
		return (0);
	if (*s1 == '\0' || *set == '\0')
		return (ft_strdup(s1));
	left_trim = 0;
	while (s1[left_trim] != '\0')
	{
		if (!ft_strchr(set, s1[left_trim]))
			break ;
		left_trim++;
	}
	right_trim = ft_strlen(s1) - 1;
	while (right_trim > left_trim)
	{
		if (!ft_strchr(set, s1[right_trim]))
			break ;
		right_trim--;
	}
	return (ft_substr(s1, left_trim, right_trim - left_trim + 1));
}
