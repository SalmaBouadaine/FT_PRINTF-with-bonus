/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 19:12:34 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/15 22:28:41 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	is_a_flag(char c)
{
	if (c == '#' || c == ' ')
		return (1);
	else if (c == '-' || c == '0' || c == '+')
		return (1);
	return (0);
}

int	invalid_format(const char *str, int len, t_flags flags)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	count += write(1, str, 1);
	if (flags.hash == 1)
		count += write(1, "#", 1);
	if (flags.plus == 1)
		count += write(1, "+", 1);
	else if (flags.space == 1)
		count += write (1, " ", 1);
	i++;
	while (is_a_flag(str[i]))
		i++;
	if (flags.dot == 1)
		count += write(1, ".", 1);
	count += ft_putnbrbase(flags.precision, "0123456789");
	i += count_digit(flags.precision, 10);
	count += write(1, str + i, len - i);
	return (count);
}

static int	is_a_conv(char c)
{
	if (c == 'c' || c == 's' || c == 'p')
		return (1);
	if (c == 'd' || c == 'i' || c == 'u')
		return (1);
	if (c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	set_flags_and_check(t_flags *flags, const char *str, int *index)
{
	int	i;

	i = *index;
	if (ft_isdigit(str[i]))
		flags->width = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
	{
		flags->dot = 1;
		i++;
	}
	if (flags->dot == 1 && ft_isdigit(str[i]))
		flags->precision = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	*index = i;
	if (is_a_conv(str[i]))
	{
		flags->letter = str[i];
		return (1);
	}
	return (0);
}

int	set_flags(t_flags *flags, const char *str)
{
	int	i;

	ft_bzero(flags, sizeof(*flags));
	i = 0;
	while (is_a_flag(str[i]))
	{
		if (str[i] == '#')
			flags->hash = 1;
		else if (str[i] == '-')
			flags->minus = 1;
		else if (str[i] == '0')
			flags->zero = 1;
		else if (str[i] == '+')
			flags->plus = 1;
		else if (str[i] == ' ')
			flags->space = 1;
		i++;
	}
	return (i);
}
