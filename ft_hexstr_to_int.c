/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexstr_to_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:20 by wchan             #+#    #+#             */
/*   Updated: 2023/09/18 18:28:58 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_pow(int base, int pow)
{
	int	res;

	res = 1;
	if (!pow)
		return (1);
	else
	{
		while (pow > 0)
		{
			res = res * base;
			pow--;
		}
	}
	return (res);
}

int	ft_hexstr_to_int(char *hexstr)
{
	int		sum;
	int		digit;
	int		pow;

	hexstr++;
	hexstr++;
	pow = ft_strlen(hexstr) - 1;
	sum = 0;
	while (*hexstr != '\0')
	{
		if (*hexstr >= 'A' && *hexstr <= 'F')
			digit = *hexstr - 'A' + 10;
		else if (*hexstr >= 'a' && *hexstr <= 'f')
			digit = *hexstr - 'a' + 10;
		else
			digit = *hexstr - '0';
		sum += digit * ft_pow(16, pow);
		pow--;
		hexstr++;
	}
	return (sum);
}
