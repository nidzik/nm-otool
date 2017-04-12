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

static void	zerone(int y)
{
	if (y == 1)
		ft_putstr("00000001");
	else if (y == 0)
		ft_putstr("00000000");
}

static void	truc(int n, int y)
{
	char	*res;
	char	*base;
	int		i;

	zerone(y);
	i = 0;
	base = "0123456789abcdef";
	res = malloc(sizeof(char) * 9);
	while (i < 9)
	{
		res[i] = '0';
		i++;
	}
	i = 7;
	while (n >= 16)
	{
		res[i--] = base[n % 16];
		n = n / 16;
	}
	res[i] = base[n % 16];
	res[8] = '\0';
	ft_putstr(res);
	free(res);
}

static void	print_value(int n, t_otool_env *e)
{
	if (e->dylink && e->cpu == 64)
		truc(n, 0);
	else if (e->lib && e->cpu == 32)
		truc(n, 2);
	else if (e->dylib || e->obj || e->lib || (e->cpu == 32 && e->fat == 1) ||\
		e->bundle)
		truc(n, 0);
	else if (e->cpu == 64)
		truc(n, 1);
	else if (e->cpu == 32)
		truc(n, 2);
}

static void	print_byte_uint8_t(uint8_t c)
{
	char *str;

	str = "0123456789abcdef";
	ft_putchar(str[(c / 16) % 16]);
	ft_putchar(str[c % 16]);
}

void		print_otool(uint32_t size, uint32_t addr, char *offset,
	t_otool_env *e)
{
	uint32_t	n;
	uint32_t	i;

	n = 0;
	if (!e->lib || e->bundle || e->dylib)
	{
		ft_putstr(e->file);
		ft_putendl(":");
	}
	ft_putendl("Contents of (__TEXT,__text) section");
	while (n < size)
	{
		print_value(addr + n, e);
		ft_putchar('\t');
		i = 0;
		while (i < 16 && n + i < size)
		{
			print_byte_uint8_t((unsigned char)(offset[n + i]));
			ft_putchar(' ');
			i++;
		}
		ft_putchar('\n');
		n += i;
	}
}
