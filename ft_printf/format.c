/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:47:00 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:27:13 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format(char fmt, va_list vl, int *result)
{
	if (fmt == 'c')
		*result += ft_putchar(va_arg(vl, int));
	else if (fmt == 's')
		*result += ft_putstr(va_arg(vl, char *));
	else if (fmt == 'd')
		ft_putnbr(va_arg(vl, int), result);
	else if (fmt == 'i')
		ft_putnbr(va_arg(vl, int), result);
	else if (fmt == 'u')
		ft_nbunsigned(va_arg(vl, unsigned int), result);
	else if (fmt == 'x')
		ft_hexadecimal(va_arg(vl, unsigned int), result, fmt);
	else if (fmt == 'X')
		ft_hexadecimal(va_arg(vl, unsigned int), result, fmt);
	else if (fmt == 'p')
		ft_pointer(va_arg(vl, void *), result);
	else
		*result += ft_putchar(fmt);
}
