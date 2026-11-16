/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 04:32:34 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/16 14:51:17 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_putptr(unsigned long n, t_flags flags)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		flags.dot = 0;
		flags.precision = 0;
		return (ft_putstr("(nil)", flags));
	}
	flags.hash = 1;
	flags.letter = 'x';
	return (ft_puthex(n, flags));
}
