/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:19:05 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/19 16:56:05 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	t;

	if ((nmemb > 0) && (SIZE_MAX / nmemb > size))
		return (0);
	t = nmemb * size;
	ptr = malloc(t);
	if (!ptr)
		return (0);
	ft_bzero(ptr, t);
	return (ptr);
}
