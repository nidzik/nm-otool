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
	ft_putnbr(c_long);
	ft_putchar('\n');
	ft_putnbr(2147483647 + c);
	return NULL;
}

t_env* init_env(t_env *e, void *ptr, int symoff, int stroff)
{
	e = (t_env *)malloc(sizeof(t_env));
	e->sym = 0;
	e->i = 0;
	e->tmp = NULL;
	e->array = ptr + symoff;
	e->array32 = ptr + symoff;
	e->stringtable = ptr + stroff;
	e->res = NULL;
	return (e);
}

void ft_boucle(t_env *e)
{
	while (e->tmp != NULL)
		{
			if ((int)(e->array[e->i].n_sect) == 0)
				{
					e->sym = 'U';
					break;
				}
			if (e->tmp->nsym != (int)(e->array[e->i].n_sect))
				{
					e->tmp = e->tmp->next;
				}
			else
				{
					if ((e->array[e->i].n_type>>0 & 1) == 0)
						e->sym = (ft_tolower(e->tmp->sym));
					else
						e->sym = (e->tmp->sym);
					break;
				}
		}
	e->res = add(e->res,e->stringtable + e->array[e->i].n_un.n_strx,\
				 ft_atoi_hex((void *)e->array[e->i].n_value, e->sym), e->sym);
}

void	print_output_64(int nsyms, int symoff, int stroff, void *ptr, t_sect *tsect)
{
	struct section_64 *sect;
	t_env *e;

	e = NULL;
	e = init_env(e, ptr, symoff, stroff);
	sect = (struct section_64 *)ptr + symoff;
	while (e->i < nsyms)
		{
			e->tmp = tsect;
			if ( (int)(((unsigned char)e->array[e->i].n_type)>>5 & 1) != 1 &&\
				 (int)(((unsigned char)e->array[e->i].n_type)>>6 & 1) != 1 &&\
				 (int)(((unsigned char)e->array[e->i].n_type)>>7 & 1) != 1\
				 )
				{
					ft_boucle(e);	
				}
			e->i++;
		}
	print_list(e->res);
	//free(res);
	//free(e->e->tmp);
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
	//	free(c);
	//	free(tsect);
}


