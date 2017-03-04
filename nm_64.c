/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 21:40:50 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/04 16:56:30 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	struct section_64 *sect;
	t_sect *tmp;
	t_res *res;
	char sym;
	
	//	tmp = tsect;
	sect = (struct section_64 *)ptr + symoff;
	//	struct segment_command_64 *seg;
	i = 0;
	array = ptr + symoff;
	stringtable = ptr + stroff;
	res = NULL;
	
	while (i < nsyms)
		{

			tmp = tsect;
				if ( (int)(((unsigned char)array[i].n_type)>>5 & 1) != 1 &&\
					 (int)(((unsigned char)array[i].n_type)>>6 & 1) != 1 &&\
					 (int)(((unsigned char)array[i].n_type)>>7 & 1) != 1\
					)
				{

					while (tmp != NULL)
						{
							//							printf("nsym:%d   sym:%c %d\n",tmp->nsym, tmp->sym, array[i].n_sect);
							if ((int)(array[i].n_sect) == 0)
							{
								sym = 'U'; 
								break;
							}
							if (tmp->nsym != (int)(array[i].n_sect))
								tmp = tmp->next;
							else
							{
								if ((array[i].n_type>>0 & 1) == 0)
									sym = (ft_tolower(tmp->sym));
								else
									sym = (tmp->sym);
								break;
							}
						}
//					ft_putchar('h');
					res = add(res,stringtable + array[i].n_un.n_strx, ft_atoi_hex((void *)array[i].n_value, sym), sym);
				}
				//			ft_putchar('l');
			i++;
		}
//	ft_putchar('p');
print_list(res);
//ft_putchar('k');
//free(res);
//free(tmp);
}



void	handle_64(void *ptr, int l, char *name)
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
	if (l == 1 || c->header->filetype == MH_OBJECT || c->header->filetype == MH_DYLIB)
		tsect->lib = 1;
	tsect->namebin = name;
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
/* 		if (tsect!=NULL) */
/* 			ft_putendl("weird"); */
/* 		else */
/* 			ft_putendl("NOP NOP NOP NOP NOP"); */
/* 		while (tsect != NULL) */
/* 			{ */
/* 				printf("\t \t seg:%s  nsym:%d  sect :%s \n",tsect->segname,tsect->nsym,tsect->sectname); */
/* 				fflush(stdout); */
/* 				tsect = tsect->next; */
/* 			} */
		//else
//	free(c);
//	free(tsect);
}


