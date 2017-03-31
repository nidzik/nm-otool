/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 21:40:50 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/04 15:59:33 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <limits.h>


void ft_boucle_32(t_env *e)
{
	while (e->tmp != NULL)
		{
			if ((int)(e->array32[e->i].n_sect) == 0)
				{
					e->sym = 'U'; 
					break;
				}
			if (e->tmp->nsym != (int)(e->array32[e->i].n_sect))
				e->tmp = e->tmp->next;
			else
				{
					if ((e->array32[e->i].n_type>>0 & 1) == 0)
						e->sym = (ft_tolower(e->tmp->sym));
					else
						e->sym = (e->tmp->sym);
					break;
				}
		}
}

void	print_output_32(int nsyms, int symoff, int stroff, void *ptr, t_sect *tsect)
{
	struct section *sect;
	t_env *e;

	e = NULL;
	e = init_env(e, ptr, symoff, stroff);
	
	sect = (struct section *)ptr + symoff;
	while (e->i < nsyms)
		{
			e->tmp = tsect;
			if ( (int)(((unsigned char)e->array32[e->i].n_type)>>5 & 1) != 1 &&\
				 (int)(((unsigned char)e->array32[e->i].n_type)>>6 & 1) != 1 &&\
				 (int)(((unsigned char)e->array32[e->i].n_type)>>7 & 1) != 1\
				 )
				{
					ft_boucle_32(e);
					if (tsect->fat == 1)
							e->res = add(e->res,e->stringtable + e->array32[e->i].n_un.n_strx, ft_atoi_hex_fat(e->array32[e->i].n_value), e->sym);
					else
							e->res = add(e->res,e->stringtable + e->array32[e->i].n_un.n_strx, ft_atoi_hex_32(e->array32[e->i].n_value, e->sym), e->sym);
				}
			e->i++;
		}
	print_list(e->res);
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
uint32_t swap_little_big(uint32_t num)
{
	uint32_t swapped;
	swapped = ((num>>24)&0xff) | // move byte 3 to byte 0
		((num<<8)&0xff0000) | // move byte 1 to byte 2
		((num>>8)&0xff00) | // move byte 2 to byte 1
		((num<<24)&0xff000000); // byte 0 to byte 3
	return(swapped);
}
void	handle_fat(void *ptr)
{
	int    i;
	t_cmds32 *c;
	t_sect *tsect;
	struct fat_arch *arch;
	struct mach_header_64 *h64;
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
	arch = (struct fat_arch *)malloc(sizeof(struct fat_arch));
	arch = (ptr + sizeof(struct fat_header *)) + sizeof(struct fat_arch);
	//	printf("off:%u\n",arch->offset/16/16);fflush(stdout);
	h64 = malloc(sizeof(struct mach_header_64));
	h64 = (void *)ptr + (swap_little_big(arch->offset));
	//	ft_putendl("lib");
	//	ft_putnbr(h64->filetype);
	//	print_byte_uint32_t(arch->offset);
	//	printf("\natoi:%s\n",ft_atoi_hex_fat(arch->offset));fflush(stdout);
	//	printf("off:%8x\n",arch->offset);fflush(stdout);
	//	printf("filetype%8x\n",h64->filetype);fflush(stdout);
	if (h64->filetype == MH_DYLIB || h64->filetype == MH_DYLINKER)
		{
			//		ft_putchar('a');
			handle_64((void *)ptr + swap_little_big(arch->offset),1,NULL);
		}
	else
		{
			//	ft_putchar('b');
			handle_64((void *)ptr + swap_little_big(arch->offset),0,NULL);
		}
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


