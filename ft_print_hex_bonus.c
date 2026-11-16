/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 19:50:12 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/16 15:11:46 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_putnbrbase(unsigned long nbr, char *base)
{
	int				count;
	unsigned long	len;
	char			c;

	count = 0;
	len = ft_strlen(base);
	if (nbr >= len)
		count += ft_putnbrbase(nbr / len, base);
	c = base[nbr % len];
	count += write(1, &c, 1);
	return (count);
}

static int	put_digits_hex(unsigned long n, char c, int len)
{
	if (c == 'x')
		return (put_digits(n, len, "0123456789abcdef"));
	else
		return (put_digits(n, len, "0123456789ABCDEF"));
}

static int	helper(unsigned long n, t_flags flags)
{
	int	count;

	count = 0;
	if (n != 0 && flags.hash == 1)
		count += write(1, "0", 1) + write(1, &flags.letter, 1);
	return (count);
}

int	puthex_helper(unsigned long n, int len, t_flags flags)
{
	int	count;
	int	prefix;

	count = 0;
	prefix = (n != 0 && flags.hash == 1) * 2;
	if (flags.zero == 1 && flags.dot == 0)
	{
		count += helper(n, flags);
		count += write_padding('0', flags.width - len - count);
		count += put_digits_hex(n, flags.letter, len);
	}
	else if (flags.precision > len)
	{
		count += write_padding(' ', flags.width - flags.precision - prefix);
		count += helper(n, flags);
		count += write_padding('0', flags.precision - len);
		count += put_digits_hex(n, flags.letter, len);
	}
	else
	{
		count += write_padding(' ', flags.width - len - prefix);
		count += helper(n, flags);
		count += put_digits_hex(n, flags.letter, len);
	}
	return (count);
}

int	ft_puthex(unsigned long n, t_flags flags)
{
	int				count;
	unsigned long	len;

	count = 0;
	len = get_len(n, 16, flags);
	if (n == 0)
	{
		if (flags.dot == 1 && flags.precision == 0)
			return (ft_putstr("", flags));
	}
	if (flags.minus == 1)
	{
		count += helper(n, flags);
		count += write_padding('0', flags.precision - len);
		count += put_digits_hex(n, flags.letter, len);
		count += write_padding(' ', flags.width - count);
	}
	else
		count += puthex_helper(n, len, flags);
	return (count);
}
