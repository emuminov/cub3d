/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:32:12 by eandre            #+#    #+#             */
/*   Updated: 2024/08/30 00:05:43 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int	validate_map_walls(char **map, t_game *g)
{
	int			i;
	t_vectori	start;

	start = get_start(map);
	if (start.y == -1 && start.x == -1)
		return (printf("\033[0;31m""Error\nThe map needs to have one player!\n"
				"\033[0m"), 1);
	g->len_tab = malloc(sizeof(int) * ft_strslen(map));
	if (g->len_tab == NULL)
		return (printf("\033[0;31m""Error\nMalloc error!\n"
				"\033[0m"), 1);
	i = -1;
	while (map[++i])
		g->len_tab[i] = (int)ft_strlen(map[i]);
	i = check_holes(map, (int)ft_strslen(map), start, g->len_tab);
	if (i == 1)
	{
		printf("\033[0;31m""Error\nThe map is not closed!\n""\033[0m");
		return (free(g->len_tab), 1);
	}
	if (i == 2)
		return (free(g->len_tab), 1);
	return (0);
}

int	check_holes(char **tab, int len_strs, t_vectori cur, int *len_tab)
{
	t_stack_stats	stack_stats;
	int				inturn;

	if (cur_border_checker(cur, len_tab, len_strs) == 1)
		return (1);
	inturn = 0;
	if (stack_stats_init(&stack_stats, len_strs, len_tab, cur) == 1)
		return (printf("\033[0;31m""Error\nMalloc error!\n""\033[0m"), 2);
	while (stack_stats.stack_size-- > 0)
	{
		cur = stack_stats.stack[stack_stats.stack_size];
		if (cur.y < 0 || cur.y >= stack_stats.len_strs || cur.x < 0 || cur.x
			>= stack_stats.len_tab[cur.y] || (tab[cur.y][cur.x] == '1'
			|| tab[cur.y][cur.x] == 'F'))
			continue ;
		tab[cur.y][cur.x] = 'F';
		manage_inturn_fill(&stack_stats, cur, &inturn);
		manage_xy_fill(tab, &stack_stats, cur);
	}
	return (free(stack_stats.stack), inturn);
}

void	manage_inturn_fill(t_stack_stats *stack_s, t_vectori cur, int *inturn)
{
	*inturn |= (cur.y == 0 || cur.y == stack_s->len_strs - 1 || cur.x == 0
			|| cur.x == stack_s->len_tab[cur.y] - 1);
	if ((cur.y + 1 < stack_s->len_strs && cur.x >= stack_s->len_tab[cur.y + 1])
		|| (cur.y - 1 < stack_s->len_strs
			&& cur.x >= stack_s->len_tab[cur.y - 1]))
		*inturn = 1;
}

void	manage_xy_fill(char **tab, t_stack_stats *stack_s, t_vectori cur)
{
	if (cur.x - 1 >= 0 && tab[cur.y][cur.x - 1] != '1'
			&& tab[cur.y][cur.x - 1] != 'F')
		stack_s->stack[stack_s->stack_size++] = (t_vectori){cur.x - 1, cur.y};
	if (cur.x + 1 < stack_s->len_tab[cur.y] && tab[cur.y][cur.x + 1] != '1'
			&& tab[cur.y][cur.x + 1] != 'F')
		stack_s->stack[stack_s->stack_size++] = (t_vectori){cur.x + 1, cur.y};
	if (cur.y - 1 >= 0 && tab[cur.y - 1][cur.x] != '1'
			&& tab[cur.y - 1][cur.x] != 'F')
		stack_s->stack[stack_s->stack_size++] = (t_vectori){cur.x, cur.y - 1};
	if (cur.y + 1 < stack_s->len_strs && tab[cur.y + 1][cur.x] != '1'
			&& tab[cur.y + 1][cur.x] != 'F')
		stack_s->stack[stack_s->stack_size++] = (t_vectori){cur.x, cur.y + 1};
}
