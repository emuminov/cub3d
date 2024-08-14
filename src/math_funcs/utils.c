/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:37:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/08/14 14:45:57 by emuminov         ###   ########.fr       */
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
		return -1;
	return 1;
}

int	max(int n1, int n2)
{
	if (n1 >= n2)
		return n1;
	return n2;
}
