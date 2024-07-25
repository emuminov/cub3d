/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:16 by eandre            #+#    #+#             */
/*   Updated: 2024/07/25 11:38:40 by eandre           ###   ########.fr       */
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

unsigned char	ft_atoc(const char *str, char *gnl, t_config_parsing *conf)
{
	unsigned char	result;
	size_t			i;

	result = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] != '\0' && str[i] != ',' && str[i] != '\n')
		while (str[i] && ft_isdigit(str[i]))
			result = (result * 10) + (str[i++] - '0');
	else
	{
		printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m");
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), -1);
	}
	if (str[i] != '\0' && str[i] != ',' && str[i] != '\n')
	{
		printf("\033[0;31m"
			"Error\nOnly number are accepted for colors!\n""\033[0m");
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), -1);
	}
	return (result);
}

void	free_config_p(t_config_parsing *conf)
{
	if (conf->north_path != NULL)
		free(conf->north_path);
	if (conf->east_path != NULL)
		free(conf->east_path);
	if (conf->south_path != NULL)
		free(conf->south_path);
	if (conf->west_path != NULL)
		free(conf->west_path);
	if (conf->floor_c != NULL)
		free(conf->floor_c);
	if (conf->ceiling_c != NULL)
		free(conf->ceiling_c);
}

void	free_config(t_config *conf)
{
	if (conf->floor_c != NULL)
		free(conf->floor_c);
	if (conf->ceiling_c != NULL)
		free(conf->ceiling_c);
	if (conf->east_fd != -1)
		close(conf->east_fd);
	if (conf->west_fd != -1)
		close(conf->west_fd);
	if (conf->north_fd != -1)
		close(conf->north_fd);
	if (conf->south_fd != -1)
		close(conf->south_fd);
}