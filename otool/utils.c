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

#include "otool.h"

void print_byte_uint8_t(uint8_t c)
{
	char *str;
	
	//printf("\n->%02x\n",(unsigned char)ptr);fflush(stdout);
	str="0123456789abcdef";
	ft_putchar(str[(c / 16) % 16]);
	ft_putchar(str[c % 16]);
}
void print_bit_uint8_t(uint8_t ptr)
{
	int i;

	i = 0;
	print_byte_uint8_t(ptr);
	while (i < 8)
		{
			ft_putchar('\t');
			ft_putnbr(ptr>>i++ & 1);
		}
	ft_putchar('\n');
}

char   *ft_atoi_hex(void *ptr, char c)
{
    char                                *base;
    unsigned long long                  address;
    char                                *hex;
    int                                 i;
	int 								check;

    base = "0123456789abcdef";
    address = (unsigned long long )ptr;
	if (c != 'U' && c != 'u' && !address)
		return ("0000000000000000");
	hex = (char *)malloc(sizeof(char) * 16);
    ft_bzero(hex, 17);
    i = 15;
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

		return (ft_strjoin("\0",hex));
//		return (hex);
        /* ft_putstr("0000000"); */
    else
        return ("                ");

}

char   *ft_atoi_hex_32(unsigned int ptr,char c)
{
    char                                *base;
    unsigned long long                  address;
    char                                *hex;
    int                                 i;
	int 								check;

    base = "0123456789abcdef";
    address = (unsigned long long )ptr;
    if (c != 'U' && c != 'u' && !address)
        return ("00000000");
	hex = (char *)malloc(sizeof(char) * 10);
    ft_bzero(hex, 10);
    i = 7;
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
		return (hex);
        /* ft_putstr("0000000"); */
    else
        return ("        ");

}

char   *ft_atoi_hex_fat(unsigned int ptr)
{
    char                                *base;
    unsigned long long                  address;
    char                                *hex;
    int                                 i;
	int 								check;

    base = "0123456789abcdef";
    address = (unsigned long long )ptr;
	hex = (char *)malloc(sizeof(char) * 10);
    ft_bzero(hex, 10);
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
		return (ft_strjoin(hex,"00000"));
        /* ft_putstr("0000000"); */
    else
        return ("                ");

}
