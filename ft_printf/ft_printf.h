/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:45:41 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:27:17 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

int		ft_printf(const char *fmt, ...);
int		ft_putchar(char c);
int		ft_putstr(char *s);
void	ft_putnbr(int nb, int *result);
void	ft_hexadecimal(unsigned int nb, int *result, char c);
void	ft_nbunsigned(unsigned int nb, int *result);
void	ft_pointer(void *n, int *result);
void	ft_hexpointer(unsigned long long nb, int *result);
void	ft_format(char fmt, va_list vl, int *result);

#endif
