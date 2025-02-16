/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:55 by eandre            #+#    #+#             */
/*   Updated: 2024/08/26 14:28:56 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

size_t	ft_strslen(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	cur_border_checker(t_vectori cur, int *len_tab, int len_strs)
{
	return (cur.y == 0 || cur.y == len_strs - 1 || cur.x == 0
		|| cur.x == len_tab[cur.y] - 1 || (cur.y + 1 < len_strs
			&& cur.x >= len_tab[cur.y + 1]) || (cur.y > 0
			&& cur.x >= len_tab[cur.y - 1]));
}

t_vectori	get_start(char **map)
{
	t_vectori	start;
	int			i;
	int			j;

	i = -1;
	start.x = -1;
	start.y = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E') && (start.y == -1 && start.x == -1))
			{
				start.y = i;
				start.x = j;
			}
			else if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E') && (start.y != -1 && start.x != -1))
				return ((t_vectori){-1, -1});
		}
	}
	return (start);
}
