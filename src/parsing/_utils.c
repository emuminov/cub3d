/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:59:16 by eandre            #+#    #+#             */
/*   Updated: 2024/08/25 02:46:20 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../libft/libft.h"
#include <stdio.h>

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

int	space_checker(int i, const char *str)
{
	while (str[i] == ' ')
		i++;
	if (ft_isspace(str[i]) == 1 && str[i] != '\n')
		return (printf("\033[0;31m"
				"Error\nOnly spaces are accepted\n""\033[0m"), 1);
	else if (str[i] != '\0' && str[i] != ',' && str[i] != '\n')
		return (printf("\033[0;31m"
				"Error\nOnly positive numbers are accepted for colors!\n"
				"\033[0m"), 1);
	return (0);
}

int	ft_atoc(const char *str, char *gnl, t_config_parsing *conf)
{
	int		result;
	size_t	i;

	result = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (ft_isspace(str[i]) == 1 && str[i] != '\n')
		return (printf("\033[0;31m""Error\nOnly spaces are accepted\n""\033[0m")
			, get_next_line(-1), free(gnl), free_config_p(conf), exit(1), -1);
	if (str[i] != '\0' && str[i] != ',' && str[i] != '\n')
		while (str[i] && ft_isdigit(str[i]))
			result = (result * 10) + (str[i++] - '0');
	else
	{
		printf("\033[0;31m""Error\nColors needs 3 numbers!\n""\033[0m");
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), -1);
	}
	if (space_checker(i, str) == 1)
		return (get_next_line(-1), free(gnl), free_config_p(conf), exit(1), -1);
	return (result);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*strs;
	size_t	len;
	int		i;
	int		j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	strs = malloc(sizeof(char) * (len + 1));
	if (strs == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		strs[i] = s1[i];
	j = 0;
	while (s2[j])
		strs[i++] = s2[j++];
	strs[i] = '\0';
	free(s1);
	return (strs);
}
