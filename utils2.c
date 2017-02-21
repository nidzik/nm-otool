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

