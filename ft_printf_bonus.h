/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 19:23:22 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/15 23:17:09 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
#define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

typedef struct s_flags
{
	int	minus;
	int	zero;
	int	dot;
	int	hash;
	int	plus;
	int	space;
	int	width;
	int	precision;
	int	letter;
}	t_flags;

int	ft_printf(const char *str, ...);
int	set_flags(t_flags *flags, const char *str);
int	set_flags_and_check(t_flags *flags, const char *str, int *index);
int	invalid_format(const char *str, int i, t_flags flags);
int	write_padding(char c, int n);
int	ft_putchar(char c, t_flags flags);
int	ft_putstr(char *str, t_flags flags);
int	ft_putnbr(int n, t_flags flags);
int	ft_putunbr(unsigned int n, t_flags flags);
int	count_digit(unsigned long n, unsigned long d);
int	get_len(unsigned long nbr, int d, t_flags flags);
int	put_digits(unsigned long nbr, int len, char *base);
int	ft_putnbrbase(unsigned long nbr, char *base);
int	ft_puthex(unsigned long n, t_flags flags);
int	ft_putptr(unsigned long n, t_flags flags);
int	ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int	ft_atoi(const char *nptr);

#endif
