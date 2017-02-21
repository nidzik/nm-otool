#include "nm.h"

char *uint8tochar(uint8_t c)
{
        char *str;
		char *ret;

		    ret = malloc(sizeof(char)*3);
        //printf("\n->%02x\n",(unsigned char)ptr);fflush(stdout);
        str="0123456789abcdef";
        ret[0] = (str[(c / 16) % 16]);
        ret[1] = (str[c % 16]);
		ret[2] = '\0';
		return (ret);
}

char *inttobyte(int c)
{
	char *str;
	char *ret;
	
	ret = malloc(sizeof(char)*3);
	//printf("\n->%02x\n",(unsigned char)ptr);fflush(stdout);
	str="0123456789abcdef";
	ret[0] = (str[(c / 16) % 16]);
	ret[1] = (str[c % 16]);
	ret[2] = '\0';
	return (ret);
}
int main()
{
	int i = 10;
	uint8_t uint8 = 10;
	int gg;

	gg = (int)uint8;
	ft_putnbr(gg);
	char *str;
	char *str1;
	str = inttobyte(i);
	str1 = uint8tochar(uint8);
	if (ft_strcmp(str,str1) == 0)
	ft_putendl(str);
	else
			ft_putendl("\\o");
	//	print_byte_uint8_t(uint8);
	return 0;
}
