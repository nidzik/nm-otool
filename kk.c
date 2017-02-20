#include "nm.h"


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
	char *str;
	str = inttobyte(i);
	ft_putendl(str);
	return 0;
}
