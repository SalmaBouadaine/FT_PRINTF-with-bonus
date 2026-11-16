/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 15:29:34 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/15 21:57:07 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_str_helper(char *str, int len, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.minus == 1)
	{
		count += write(1, str, len);
		count += write_padding(' ', flags.width - len);
	}
	else
	{
		count += write_padding(' ', flags.width - len);
		count += write(1, str, len);
	}
	return (count);
}

static int	helper(char *str, t_flags flags)
{
	int	len;
	int	count;

	count = 0;
	len = ft_strlen(str);
	if (flags.dot == 0)
		count += ft_str_helper(str, len, flags);
	else
	{
		if (flags.precision < len)
			count += ft_str_helper(str, flags.precision, flags);
		else
			count += ft_str_helper(str, len, flags);
	}
	return (count);
}

int	ft_putstr(char *str, t_flags flags)
{
	if (str == NULL)
	{
		if (flags.dot == 1 && flags.precision > 5)
			return (helper("(null)", flags));
		if (flags.dot == 0 && flags.width == 0)
			return (helper("(null)", flags));
		else
			return (0);
	}
	return (helper(str, flags));
}
