/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerique.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:46:28 by hrandria          #+#    #+#             */
/*   Updated: 2023/10/10 21:11:34 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nb, int *result)
{
	char	n;

	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*result) += 11;
	}
	else
	{
		if (nb < 0)
		{
			nb = nb * -1;
			*result += ft_putchar('-');
		}
		if (nb > 9)
		{
			ft_putnbr(nb / 10, result);
			ft_putnbr(nb % 10, result);
		}
		else
		{
			n = nb + '0';
			*result += ft_putchar(n);
		}
	}
}

void	ft_nbunsigned(unsigned int nb, int *result)
{
	unsigned char	n;

	if (nb > 9)
	{
		ft_putnbr(nb / 10, result);
		ft_putnbr(nb % 10, result);
	}
	else
	{
		n = nb + '0';
		(*result)++;
		write(1, &n, 1);
	}
}

void	ft_hexadecimal(unsigned int nb, int *result, char c)
{
	char	*hexa;

	if (nb == 0)
	{
		write(1, "0", 1);
		*result += 1;
	}
	else
	{
		if (c == 'x')
			hexa = "0123456789abcdef";
		else
			hexa = "0123456789ABCDEF";
		if (nb >= 16)
		{
			ft_hexadecimal(nb / 16, result, c);
			ft_hexadecimal(nb % 16, result, c);
		}
		else
		{
			(*result)++;
			write(1, &hexa[nb], 1);
		}
	}
}

void	ft_hexpointer(unsigned long long nb, int *result)
{
	char			*hexa;
	int				n;

	hexa = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_hexpointer(nb / 16, result);
		ft_hexpointer(nb % 16, result);
	}
	else
	{
		n = (int)nb;
		(*result)++;
		write(1, &hexa[n], 1);
	}
}

void	ft_pointer(void *n, int *result)
{
	unsigned long long	s;

	s = (unsigned long long)n;
	if (n == 0)
	{
		write(1, "(nil)", 5);
		*result += 5;
	}
	else
	{
		ft_putchar('0');
		ft_putchar('x');
		*result += 2;
		ft_hexpointer(s, result);
	}
}
