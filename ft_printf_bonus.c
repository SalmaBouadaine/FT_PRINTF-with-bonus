/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 23:12:05 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/15 22:04:44 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_helper(va_list *list, t_flags flags)
{
	if (flags.letter == 'c')
		return (ft_putchar(va_arg(*list, int), flags));
	else if (flags.letter == 's')
		return (ft_putstr(va_arg(*list, char *), flags));
	else if (flags.letter == 'p')
		return (ft_putptr(va_arg(*list, unsigned long), flags));
	else if (flags.letter == 'd' || flags.letter == 'i')
		return (ft_putnbr(va_arg(*list, int), flags));
	else if (flags.letter == 'u')
		return (ft_putunbr(va_arg(*list, unsigned int), flags));
	else if (flags.letter == 'x' || flags.letter == 'X')
		return (ft_puthex(va_arg(*list, unsigned int), flags));
	else if (flags.letter == '%')
		return (ft_putchar('%', flags));
	else
		return (-1);
}

static int	ft_printf_helper(const char *str, int *i, va_list *list)
{
	t_flags		flags;
	const char	*start;
	int			j;
	int			res;

	start = str + *i;
	j = set_flags(&flags, start + 1);
	if (set_flags_and_check(&flags, start + 1, &j) == 0)
	{
		if (start[j + 1] == '\0')
			return (-1);
		res = invalid_format(start, j + 2, flags);
	}
	else
		res = ft_helper(list, flags);
	*i = *i + 1 + j;
	return (res);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		rtrn;
	int		i;
	int		check;

	i = 0;
	rtrn = 0;
	if (!str)
		return (-1);
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
			check = ft_printf_helper(str, &i, &list);
		else
			check = write(1, &str[i], 1);
		if (check < 0)
			return (va_end(list), -1);
		else
			rtrn += check;
		i++;
	}
	va_end(list);
	return (rtrn);
}
