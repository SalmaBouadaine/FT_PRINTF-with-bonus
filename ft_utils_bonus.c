/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 22:27:34 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/15 22:27:52 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static const char	*skip_spaces(const char	*nptr)
{
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	return (nptr);
}

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	sign;
	int	i;

	sign = 1;
	nbr = 0;
	i = 0;
	nptr = skip_spaces(nptr);
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	else if (nptr[i] < '0' || nptr[i] > '9')
		return (nbr);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (nbr * sign);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*b;
	size_t			i;

	b = s;
	i = 0;
	while (i < n)
	{
		b[i] = 0;
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
