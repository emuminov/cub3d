/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:16 by eandre            #+#    #+#             */
/*   Updated: 2024/07/17 20:03:25 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	charcmp(char *str, char c)
{
	int	i;
	int	inturn;

	i = 0;
	inturn = 0;
	while (str[i])
	{
		if (str[i] == c)
			inturn++;
		i++;
	}
	return (inturn);
}

unsigned char	ft_atoc(const char *str)
{
	unsigned char	result;
	size_t			i;

	result = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		result = (result * 10) + (str[i++] - '0');
	return (result);
}

void	free_config(t_config *config)
{
	if (config->north_path != NULL)
		free(config->north_path);
	if (config->east_path != NULL)
		free(config->east_path);
	if (config->south_path != NULL)
		free(config->south_path);
	if (config->west_path != NULL)
		free(config->west_path);
	if (config->floor_color != NULL)
		free(config->floor_color);
	if (config->ceiling_color != NULL)
		free(config->ceiling_color);
}
