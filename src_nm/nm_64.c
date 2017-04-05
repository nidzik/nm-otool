/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 21:40:50 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/31 17:27:19 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <limits.h>

void	free_tsect(t_sect *t)
{
	t_sect	*tmp;
	
	if (t == NULL)
		return ;
	tmp = t;
//	while (tmp->next)
	{
		tmp = t->next;
		free(t);
		free_tsect(tmp);
	}
}

t_env	*init_env(t_env *e, void *ptr, int symoff, int stroff)
{
	e->sym = 0;
	e->i = 0;
	e->tmp = NULL;
	e->array = ptr + symoff;
	e->array32 = ptr + symoff;
	e->stringtable = ptr + stroff;
	e->res = NULL;
	return (e);
}

void	ft_boucle(t_env *e)
{
	char c;
	char mask;
	
	c = e->array[e->i].n_type;
	mask = c & N_TYPE;
//	ft_putendl("MASK");
	while (e->tmp != NULL)
	{
		if (mask == N_INDR)
		{
			e->sym = 'I';
			break ;
		}
		else if (mask == N_ABS)
		{
			e->sym = 'A';
			break;
		}
		else if ((int)(e->array[e->i].n_sect) == 0)
		{
			e->sym = 'U';
			break ;
		}
		if (e->tmp->nsym != (int)(e->array[e->i].n_sect))
		{
			e->tmp = e->tmp->next;
		}
		else
		{
			if ((e->array[e->i].n_type >> 0 & 1) == 0)
			{
				e->sym = (ft_tolower(e->tmp->sym));
//				printf("gg");fflush(stdout);
			}
			else
				e->sym = (e->tmp->sym);
			break ;
		}
	}
	e->res = add(e->res, e->stringtable + e->array[e->i].n_un.n_strx, \
				ft_atoi_hex((void *)e->array[e->i].n_value, e->sym), e->sym);
}

void	print_output_64(t_cmds *c, void *ptr, \
						t_sect *tsect)
{
	struct section_64	*sect;
	t_env				*e;

	e = (t_env *)malloc(sizeof(t_env));
	e = init_env(e, ptr, c->sym->symoff, c->sym->stroff);
	sect = (struct section_64 *)ptr + c->sym->symoff;
	while (e->i < (int)c->sym->nsyms)
	{
		e->tmp = tsect;
		if ((int)(((unsigned char)e->array[e->i].n_type) >> 5 & 1) != 1 && \
			(int)(((unsigned char)e->array[e->i].n_type) >> 6 & 1) != 1 && \
			(int)(((unsigned char)e->array[e->i].n_type) >> 7 & 1) != 1)
		{
			ft_boucle(e);
		}
		e->i++;
	}
	print_list(e->res);
//	if (tsect->ac > 2)
//		free_tsect(tsect);
	free(e);
}

void	handle_64(void *ptr, int l, char *name, int ac)
{
	int		i;
	t_cmds	*c;
	t_sect	*tsect;

	tsect = malloc(sizeof(t_sect));
	lst_init(tsect);
	tsect->ac = ac;
	c = (t_cmds *)malloc(sizeof(c));
	c->header = (struct mach_header_64 *)ptr;
	c->ncmds = c->header->ncmds;
	c->lc = (void *)ptr + sizeof(*(c->header));
	if (l == 1 || c->header->filetype == MH_OBJECT || \
		c->header->filetype == MH_DYLIB)
		tsect->lib = 1;
	tsect->namebin = name;
//	tsect->statik = 0;
	i = 0;
	while (i < c->ncmds)
	{
		if (c->lc->cmd == LC_SEGMENT_64)
			tsect = get_seg_table((void *)c->lc, tsect);
		if (c->lc->cmd == LC_SYMTAB)
		{
			c->sym = (struct symtab_command *)c->lc;
			print_output_64(c, ptr, tsect);
//			tsect->statik = 0;
//	free_tsect(tsect);
			break ;
		}
		c->lc = (void *)c->lc + c->lc->cmdsize;
		i++;

	}
	free(c);
}