/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:32:46 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/29 05:46:41 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static Flags	*flags_singleton(void)
{
	static Flags	obj;

	return (&obj);
}
#define this flags_singleton()

static const uint8_t b_map[128] = 
{
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	16,	0,	0,	8,	0,	64,	0,	0,
	0,	0,	0,	32,	0,	1,	4,	0,	2,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	64,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	64,
	64,	0,	0,	0,	0,	64,	0,	0,	0,	0,
	0,	0,	64,	0,	0,	64,	0,	64,	0,	0,
	64,	0,	0,	0,	0,	0,	0,	0
};

void	init(const char **s)
{
	if (b_map[*++(*s)] & B_FORMAT_SPECIFIER)
		return;
	if (b_map[**s])
	{
		this->flags |= b_map[**s];
		if (b_map[**s] & B_DOT_FLAG)
			while (isdigit(**s))
				this->precision = this->precision * 10 + *(*s)++ - '0';
	}
	else if (isdigit(**s))
		while (isdigit(**s))
			this->field_width = this->field_width * 10 + *(*s)++ - '0';
	init(s);
}

void	reset(void)
{
	this->flags = B_RESET;
	this->field_width = 0;
	this->precision = 0;
}

bool	is_flag_set(uint16_t flag)
{
	return (this->flags & flag);
}

void	print_flags(void)
{
	printf("flags | B_MINUS_FLAG : %d\n", this->is_flag_set(B_MINUS_FLAG));
	printf("flags | B_ZERO_FLAG : %d\n", this->is_flag_set(B_ZERO_FLAG));
	printf("flags | B_DOT_FLAG : %d\n", this->is_flag_set(B_DOT_FLAG));
	printf("flags | B_HASHTAG_FLAG : %d\n", this->is_flag_set(B_HASHTAG_FLAG));
	printf("flags | B_SPACE_FLAG : %d\n", this->is_flag_set(B_SPACE_FLAG));
	printf("flags | B_PLUS_FLAG : %d\n", this->is_flag_set(B_PLUS_FLAG));
	printf("flags | FORMAT_IDENTIFIER : %d\n", this->flags & B_FORMAT_SPECIFIER);
	printf("flags | FIELD_WIDTH : %d\n", this->field_width);
	printf("flags | PRECISION : %d\n", this->precision);
}

Flags	*flags_construct(void)
{
	this->init = &init;
	this->reset = &reset;
	this->is_flag_set = &is_flag_set;
	this->print_flags = &print_flags;
	return (this);
}