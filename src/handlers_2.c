/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:20:08 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/10 02:52:00 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

static const char	g_char_table[49] = {
	0,		'-',	0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		' ',	'-',	0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		'+',	'-',	0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		0,		'+',	'-'
};

void	handle_decimal(t_func f, t_printer	*p)
{
	int	arg;

	arg = va_arg(p->args, int);
	p->sign = arg < 0;
	p->sign |= p->flags & (B_PLUS_FLAG | B_SPACE_FLAG);
	if (p->sign)
		f(g_char_table[p->sign], p);
	p->sign = 0;//(p->sign && !p->prec);
	bufferize_integer((unsigned int)ft_abs(arg), g_base_10, f, p);
}

void	handle_pointer(t_func f, t_printer *p)
{
	unsigned long	arg;

	arg = va_arg(p->args, unsigned long);
	if (arg)
	{
		bufferize_string("0x", f, p);
		bufferize_integer(arg, g_base_16, f, p);
	}
	else
		bufferize_string("(nil)", f, p);
}

void	handle_unsigned(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	bufferize_integer(arg, g_base_10, f, p);
}

void	bufferize_integer(unsigned long n, t_base base, t_func f, \
							t_printer *p)
{
	if (n >= (unsigned long)base.size)
	{
		bufferize_integer(n / base.size, base, f, p);
		f(base.string[n % base.size], p);
	}
	else
		f(base.string[n], p);
}
