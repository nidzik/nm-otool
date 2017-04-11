/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_otool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 16:51:20 by jwalle            #+#    #+#             */
/*   Updated: 2016/11/26 16:51:22 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_value(int n, t_otool_env *e)
{
	if (e->dylink && e->cpu == 64)
		printf("00000000%08x", n);
	else if (e->lib && e->cpu == 32)
		printf("%08x", n);
	else if (e->dylib || e->obj || e->lib || (e->cpu == 32 && e->fat == 1) ||\
		e->bundle)
		printf("00000000%08x", n);
	else if (e->cpu == 64)
		printf("00000001%08x", n);
	else if (e->cpu == 32)
		printf("%08x", n);
}

void		print_otool(uint32_t size, uint32_t addr, char *offset,
	t_otool_env *e)
{
	uint32_t	n;
	uint32_t	i;

	n = 0;
	if (!e->lib || e->bundle || e->dylib)
		printf("%s:\n", e->file);
	printf("Contents of (__TEXT,__text) section\n");
	while (n < size)
	{
		print_value(addr + n, e);
		printf("\t");
		i = 0;
		while (i < 16 && n + i < size)
		{
			printf("%.2x ", (unsigned char)(offset[n + i]));
			i++;
		}
		printf("\n");
		n += i;
	}
}
