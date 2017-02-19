#include "nm.h"

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

void	ft_atoi_hex(void *ptr)
{
    char                                *base;
    unsigned long long                  address;
    char                                hex[10];
    int                                 i;

    base = "0123456789abcdef";
    address = (unsigned long long )ptr;
    ft_bzero(hex, 10);
    i = 8;
    while (address)
    {
        hex[i] = base[address % 16];
        address = address / 16;
        i--;
    }
    if (hex[0])
        ft_putstr("0000000");
    else
        ft_putstr("                ");
    ft_putstr(hex);

}
