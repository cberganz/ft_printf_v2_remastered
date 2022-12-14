/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:20:08 by cberganz          #+#    #+#             */
/*   Updated: 2023/01/07 15:07:18 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

static const char	g_char_table[50] = {
	0,		'-',	0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		' ',	'-',	0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		'+',	'-',	0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		'+',	'-'
};

void	handle_decimal(t_func f, t_printer	*p)
{
	int	arg;

	arg = va_arg(p->args, int);
	*p->sign = arg < 0;
	*p->sign |= p->f & (F_PLUS | F_SPACE);
	if (*p->sign)
		*p->sign = g_char_table[(int)*p->sign];
	if (!(!arg && (p->f & F_DOT) && p->p == 0))
		bufferize_integer((unsigned int)ft_abs(arg), g_base_10, f, p);
}

void	handle_pointer(t_func f, t_printer *p)
{
	unsigned long	arg;

	arg = va_arg(p->args, unsigned long);
	if (arg)
	{
		ft_strcpy(p->sign, "0x");
		bufferize_integer(arg, g_base_16, f, p);
	}
	else
	{
		p->f &= ~F_DOT;
		bufferize_string("(nil)", f, p);
	}
}

void	handle_unsigned(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	if (!(!arg && (p->f & F_DOT) && p->p == 0))
		bufferize_integer(arg, g_base_10, f, p);
}

void	bufferize_integer(unsigned long n, t_base base, t_func f, \
							t_printer *p)
{
	if (p->malloc_error)
		return ;
	if (n >= (unsigned long)base.size)
	{
		bufferize_integer(n / base.size, base, f, p);
		f(base.string[n % base.size], p, false);
	}
	else
		f(base.string[n], p, false);
}

void	handle_percent(t_func f, t_printer *p)
{
	f('%', p, false);
	p->w = 0;
	p->p = 0;
}
