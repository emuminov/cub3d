/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:33:37 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/19 16:39:19 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((char) c == '\0')
		return ((char *) &(s[i]));
	while (1)
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		if (i == 0)
			break ;
		i--;
	}
	return (0);
}
