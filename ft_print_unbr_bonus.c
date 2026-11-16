/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unbr_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 15:31:33 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/15 21:56:48 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	count_digit(unsigned long n, unsigned long d)
{
	int	count;

	count = 1;
	while (n >= d)
	{
		n = n / d;
		count++;
	}
	return (count);
}

int	get_len(unsigned long nbr, int d, t_flags flags)
{
	if (nbr == 0 && flags.dot == 1 && flags.precision == 0)
		return (0);
	return (count_digit(nbr, d));
}

static int	ft_putunbr_helper(unsigned int n)
{
	int		count;
	char	c;

	count = 0;
	if (n >= 10)
		count += ft_putunbr_helper(n / 10);
	c = (n % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}

static int	ft_helper(unsigned int n, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.minus == 1)
	{
		count += write_padding('0', flags.precision - count_digit(n, 10));
		count += ft_putunbr_helper(n);
		count += write_padding(' ', flags.width - count);
	}
	else
	{
		if (flags.precision > count_digit(n, 10))
			count += write_padding(' ', flags.width - flags.precision);
		else
		{
			if (flags.zero == 1 && flags.dot == 0)
				count += write_padding('0', flags.width - count_digit(n, 10));
			else
				count += write_padding(' ', flags.width - count_digit(n, 10));
		}
		count += write_padding('0', flags.precision - count_digit(n, 10));
		count += ft_putunbr_helper(n);
	}
	return (count);
}

int	ft_putunbr(unsigned int n, t_flags flags)
{
	if (n == 0)
	{
		if (flags.dot == 1 && flags.precision == 0)
			return (ft_putstr("", flags));
	}
	return (ft_helper(n, flags));
}
