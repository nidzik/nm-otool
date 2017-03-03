/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 21:40:50 by nidzik            #+#    #+#             */
/*   Updated: 2017/02/26 21:31:19 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <limits.h>

void	print_output_32(int nsyms, int symoff, int stroff, void *ptr, t_sect *tsect)
{
	int i;
	char *stringtable;
	struct nlist *array;
	struct section *sect;
	t_sect *tmp;
	t_res *res;
	char sym;
	
	sect = (struct section *)ptr + symoff;
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
					if (tsect->fat == 1)
					res = add(res,stringtable + array[i].n_un.n_strx, ft_atoi_hex_fat(array[i].n_value), sym);
					else
						res = add(res,stringtable + array[i].n_un.n_strx, ft_atoi_hex_32(array[i].n_value, sym), sym);
				}
			i++;
		}
print_list(res);
}



void	handle_32(void *ptr, int l, char *name)
{
	int    i;
	t_cmds32 *c;
	t_sect *tsect;

  	tsect = malloc(sizeof(t_sect));
	lst_init(tsect);
	c = ( t_cmds32 *)malloc(sizeof(c));
	tsect->fat = 0;
	c->header = (struct mach_header *) ptr;
	c->ncmds = c->header->ncmds;
	c->lc = (void *)ptr + sizeof(*(c->header));
	    if (l == 1 || c->header->filetype == MH_OBJECT)
        tsect->lib = 1;
    tsect->namebin = name;
	i = 0;
	while (i < c->ncmds)
		{
			if (c->lc->cmd == LC_SEGMENT)
				tsect = get_seg_table_32((void *)c->lc, tsect);
  			if (c->lc->cmd == LC_SYMTAB)
				{
					c->sym = (struct symtab_command *) c->lc;
					print_output_32(c->sym->nsyms, c->sym->symoff,c->sym->stroff, ptr,tsect);
					break;
				}
			c->lc = (void *) c->lc + c->lc->cmdsize;
			i++;
		}
}

void	handle_fat(void *ptr)
{
	int    i;
	t_cmds32 *c;
	t_sect *tsect;
	struct fat_arch *arch;
	
	//		int magic_number;
	//	arch = ptr;a//
	//ptr = (void *)ptr + 4096;
  	tsect = malloc(sizeof(t_sect));
	lst_init(tsect);
	c = ( t_cmds32 *)malloc(sizeof(c->header));
	tsect->fat = 1;
	c->header = (struct mach_header *) ptr;
	c->ncmds = c->header->ncmds;
	c->lc = (void *)ptr + sizeof(*(c->header));
	arch = (struct fat_arch *)ptr  + sizeof(arch);
	handle_64((void *)ptr + arch->offset,0,NULL);
	return;
	//	magic_number = *((int *)((void *)ptr + 4096));
	//if (magic_number == (int)MH_MAGIC_64)
	//		ft_putendl("magic");
	//	else
	//					ft_putendl("nop");
	//		if (nm_type((void *)ptr + 4096, 2, NULL) == 1)
	//			return;
	   
	i = 0;
	while (i < c->ncmds)
		{
			if (c->lc->cmd == LC_SEGMENT)
				tsect = get_seg_table_32((void *)c->lc, tsect);
  			if (c->lc->cmd == LC_SYMTAB)
				{
					c->sym = (struct symtab_command *) c->lc;
					print_output_32(c->sym->nsyms, c->sym->symoff,c->sym->stroff, ptr,tsect);
					break;
				}
			c->lc = (void *) c->lc + c->lc->cmdsize;
			i++;
		}
}


