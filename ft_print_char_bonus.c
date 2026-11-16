/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:54:46 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/15 21:58:28 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	write_padding(char c, int n)
{
	int	count;

	count = 0;
	while (count < n)
	{
		if (write(1, &c, 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_putchar(char c, t_flags flags)
{
	int	count;
	int	check;

	count = 0;
	if (flags.minus == 0)
	{
		check = write_padding(' ', flags.width - 1);
		if (check == -1)
			return (-1);
		count += check;
	}
	if (write(1, &c, 1) == -1)
		return (-1);
	count++;
	if (flags.minus == 1)
	{
		check = write_padding(' ', flags.width - 1);
		if (check == -1)
			return (-1);
		count += check;
	}
	return (count);
}
