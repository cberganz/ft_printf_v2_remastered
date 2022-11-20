/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:41:38 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/19 14:26:47 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../ft_printf.h"

int	main(int argc, char *argv[])
{
	int	size;

	size = 0;
	while (size < 200000)
	{
		ft_printf("1--------------------------------------------------------- \
				------------------------------------------100---------------- \
				------------------------------------------------------------- \
				--------------------200-------------------------------------- \
				-----------------------------------------------------------30 \
				0------------------------------------------------------------ \
				-------------------------------------400--------------------- \
				------------------------------------------------------------- \
				---------------500------------------------------------------- \
				------------------------------------------------------600---- \
				------------------------------------------------------------- \
				--------------------------------700-------------------------- \
				------------------------------------------------------------- \
				----------800------------------------------------------------ \
				-------------------------------------------------900--------- \
				------------------------------------------------------------- \
				---------------------------");
		size++;
	}
	return (0);
}
