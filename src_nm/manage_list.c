/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:54:14 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/31 17:03:30 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	cmp_segtxt(t_sect *sect)
{
	if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
		sect->sym = 'T';
	else
		sect->sym = 'S';
}

void	cmp_segdata(t_sect *sect)
{
	if (ft_strcmp(sect->sectname, SECT_BSS) == 0)
		sect->sym = 'B';
	else if (ft_strcmp(sect->sectname, SECT_DATA) == 0)
	{
		sect->sym = 'D';
	}
	else
		sect->sym = 'S';
}

void	fill_sym(t_sect *sect)
{
	if (ft_strcmp(sect->segname, SEG_TEXT) == 0)
		cmp_segtxt(sect);
	else if (ft_strcmp(sect->segname, SEG_DATA) == 0)
		cmp_segdata(sect);
	else if (ft_strcmp(sect->segname, SEG_OBJC) == 0)
		sect->sym = 'S';
	else if (ft_strcmp(sect->segname, SEG_IMPORT) == 0 ||\
			ft_strcmp(sect->segname, "__la_symbol_ptr") == 0)
		sect->sym = 'I';
	else if (sect->lib == 1)
	{
		cmp_segtxt(sect);
		if (sect->sym != 'T')
			cmp_segdata(sect);
	}
	else
		sect->sym = 'U';
}

void	lst_init(t_sect *tsect)
{
	tsect->segname = NULL;
	tsect->sectname = NULL;
	tsect->nsym = 0;
	tsect->sym = 0;
	tsect->fat = 0;
	tsect->lib = 0;
	tsect->ac = 0;
	tsect->statik = 0;
	tsect->namebin = NULL;
	tsect->next = NULL;
	tsect->sizefile = 0;
}

void	lst_add(t_sect *tsect, char *seg, \
				char *sect, int i)
{
	t_sect		*tmp;
	t_sect		*new;

	tmp = tsect;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new = malloc(sizeof(t_sect));
	new->segname = seg;
	new->sectname = sect;
	new->sym = 0;
	if (i == 0 && ft_strcmp(seg, SEG_PAGEZERO) != 0)
		i++;
	new->nsym = tsect->statik++;
	if (tmp->lib == 1)
	{
		new->lib = 1;
		new->nsym = tmp->nsym + 1;
	}
	new->next = NULL;
	fill_sym(new);
	if (tsect->ac == 100)
		new->sym = 'I';
	tsect->ac = 0;
	tmp->next = new;
}
