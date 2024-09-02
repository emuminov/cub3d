/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre <eandre@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/09/02 15:55:25 by eandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	abs_f(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

double	sign_f(double nbr)
{
	if (nbr < 0)
		return (-1);
	else if (nbr > 0)
		return (1);
	return (0);
}

int	max(int n1, int n2)
{
	if (n1 >= n2)
		return (n1);
	return (n2);
}

int	normalize(int value, int min, int max)
{
	int	normalized_value;

	normalized_value = (value - min) / (max - min);
	return (normalized_value);
}
