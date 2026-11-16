/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 15:18:54 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/15 22:20:43 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	get_sign(int n, t_flags flags)
{
	if (n < 0)
		return ('-');
	if (flags.plus == 1)
		return ('+');
	if (flags.space == 1)
		return (' ');
	return ('n');
}

static int	put_sign(char c)
{
	if (c != 'n')
		return (write (1, &c, 1));
	return (0);
}

int	put_digits(unsigned long nbr, int len, char *base)
{
	if (len == 0)
		return (0);
	return (ft_putnbrbase(nbr, base));
}

static int	putnbr_helper(long nbr, char c, int len, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.zero == 1 && flags.dot == 0)
	{
		count += put_sign(c);
		count += write_padding('0', flags.width - len);
		count += put_digits(nbr, len, "0123456789");
	}
	else if (flags.precision > len)
	{
		count += write_padding(' ', flags.width - flags.precision);
		count += put_sign(c);
		count += write_padding('0', flags.precision - len);
		count += put_digits(nbr, len, "0123456789");
	}
	else
	{
		count += write_padding(' ', flags.width - len);
		count += put_sign(c);
		count += put_digits(nbr, len, "0123456789");
	}
	return (count);
}

int	ft_putnbr(int n, t_flags flags)
{
	int		count;
	char	c;
	int		len;
	long	nbr;

	count = 0;
	nbr = n;
	c = get_sign(n, flags);
	if (nbr < 0)
		nbr = -nbr;
	len = get_len(nbr, 10, flags);
	if (c != 'n')
		flags.width--;
	if (flags.minus == 1)
	{
		count += put_sign(c);
		if (len == 0)
			count += write_padding(' ', flags.width);
		else
			count += ft_putunbr(nbr, flags);
	}
	else
		count += putnbr_helper(nbr, c, len, flags);
	return (count);
}
