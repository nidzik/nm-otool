#include "nm.h"
#include <limits.h>

char *ft_itohex(int c)
{
	unsigned long long int c_long;

	c_long = (unsigned long long int)c;
    //printf("  prtinf zu \t%llu\n ",c_long);
	ft_putnbr(c_long);
	ft_putchar('\n');
	ft_putnbr(2147483647 + c);
	return NULL;
}

void	print_output_64(int nsyms, int symoff, int stroff, void *ptr, t_sect *tsect)
{
	int i;
	char *stringtable;
	struct nlist_64 *array;
	uint32_t op;
	struct section_64 *sect;

	sect = (struct section_64 *)ptr + symoff;
	//	struct segment_command_64 *seg;
	i = 0;
	array = ptr + symoff;
	stringtable = ptr + stroff;
	op = 0;
	while (i < nsyms)
		{
			//			if (array[i].n_sect == 0)
			//				if ( (int)(((unsigned char)array[i].n_type)>>0 & 1) == N_EXT)
				if ( (int)(((unsigned char)array[i].n_type)>>5 & 1) != 1 &&\
					 (int)(((unsigned char)array[i].n_type)>>6 & 1) != 1 &&\
					 (int)(((unsigned char)array[i].n_type)>>7 & 1) != 1\
					)
				{
					printf("%hhu\t  ",array[i].n_sect); 
					print_byte_uint8_t(array[i].n_sect);
					ft_atoi_hex((void *)array[i].n_value);
					while (tsect != NULL || ft_strcmp((char*)tsect->sym,(char*)array[i].n_sect)==0)
						tsect = tsect->next;

/* 					if ((array[i].n_sect >> 0 & 1) == 1) */
/* 						ft_putstr(" T "); */
/* 					else */
/* 						ft_putstr(" U "); */
					
				ft_putendl(stringtable + array[i].n_un.n_strx);
				//ft_atoi_hex(stringtable + array[i].n_un.n_strx);

				}

			i++;
		}
}

void	handle_64(void *ptr)
{
	int    i;
	t_cmds *c;
	t_sect *tsect;

  	tsect = malloc(sizeof(t_sect));
	lst_init(tsect);
	c = ( t_cmds *)malloc(sizeof(c));
	c->header = (struct mach_header_64 *) ptr;
	c->ncmds = c->header->ncmds;
	c->lc = (void *)ptr + sizeof(*(c->header)); 
	i = 0;
	while (i < c->ncmds)
		{
			if (c->lc->cmd == LC_SEGMENT_64)
				tsect = get_seg_table((void *)c->lc, tsect);
  			if (c->lc->cmd == LC_SYMTAB)
				{
					c->sym = (struct symtab_command *) c->lc;
					print_output_64(c->sym->nsyms, c->sym->symoff,c->sym->stroff, ptr,tsect);
					break;
				}
			c->lc = (void *) c->lc + c->lc->cmdsize;
			i++;
		}
	//	get_sect((void *)c->lc);
		if (tsect!=NULL)
			ft_putendl("weird");
		else
			ft_putendl("NOP NOP NOP NOP NOP");
		while (tsect != NULL)
			{
				printf("\t \t seg:%s  nsym:%d  sect :%s \n",tsect->segname,tsect->nsym,tsect->sectname);
				fflush(stdout);
				tsect = tsect->next;
			}
		//else

	//	free(array);
}


