/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 17:47:10 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/04 16:19:32 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_byte_uint8_t(uint8_t c)
{
	char *str;

	str = "0123456789abcdef";
	ft_putchar(str[(c / 16) % 16]);
	ft_putchar(str[c % 16]);
}

void	print_bit_uint8_t(uint8_t ptr)
{
	int i;

	i = 0;
	print_byte_uint8_t(ptr);
	while (i < 8)
	{
		ft_putchar('\t');
		ft_putnbr(ptr >> i++ & 1);
	}
	ft_putchar('\n');
}

char	*ft_atoi_hex(void *ptr, char c)
{
	t_atoi *a;

	a = (t_atoi *)malloc(sizeof(t_atoi));
	a->base = "0123456789abcdef";
	a->address = (unsigned long long)ptr;
	if (c != 'U' && c != 'u' && !a->address)
		return ("0000000000000000");
	init_atoi(a);
	while (a->address)
	{
		a->check = 1;
		a->hex[a->i] = a->base[a->address % 16];
		a->address = a->address / 16;
		a->i--;
	}
	if (a->i != 0 && a->check == 1)
		while (a->i >= 0)
			a->hex[a->i--] = '0';
	if (a->check == 1)
	{
		a->hex[16] = '\0';
		return (a->hex);
	}
	else
		return ("                ");
}

char	*ft_atoi_hex_32(unsigned int ptr, char c)
{
	t_atoi *a;

	a = (t_atoi *)malloc(sizeof(t_atoi));
	a->base = "0123456789abcdef";
	a->address = (unsigned long long)ptr;
	if (c != 'U' && c != 'u' && !a->address)
		return ("00000000");
	a->hex = (char *)malloc(sizeof(char) * 10);
	a->i = 7;
	a->check = 0;
	while (a->address)
	{
		a->check = 1;
		a->hex[a->i] = a->base[a->address % 16];
		a->address = a->address / 16;
		a->i--;
	}
	if (a->i != 0 && a->check == 1)
		while (a->i >= 0)
			a->hex[a->i--] = '0';
	if (a->check == 1)
		return (ft_strjoin("\0", a->hex));
	else
		return ("        ");
}

char	*ft_atoi_hex_fat(unsigned int ptr)
{
	char							*base;
	unsigned long long				address;
	char							*hex;
	int								i;
	int								check;

	base = "0123456789abcdef";
	address = (unsigned long long)ptr;
	hex = (char *)malloc(sizeof(char) * 10);
	i = 10;
	check = 0;
	while (address)
	{
		check = 1;
		hex[i] = base[address % 16];
		address = address / 16;
		i--;
	}
	if (i != 0 && check == 1)
		while (i >= 0)
			hex[i--] = '0';
	if (check == 1)
		return (ft_strjoin(hex, "00000"));
	else
		return ("                ");
}
