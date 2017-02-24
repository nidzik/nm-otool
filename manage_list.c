/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:54:14 by nidzik            #+#    #+#             */
/*   Updated: 2017/02/23 15:29:41 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void cmp_segtxt(t_sect *sect)
{
	if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
        sect->sym = 'T';
	else
		sect->sym = 's';
}

void fill_sym(t_sect *sect)
{
	if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
		{
			cmp_segtxt(sect);
				//			return;
		}
	else if (ft_strcmp(sect->sectname, SECT_BSS) == 0)
        sect->sym = 'b';
	else if (ft_strcmp(sect->sectname, SECT_COMMON) == 0)
        sect->sym = 'C';
	else
		sect->sym = 'U';
}

void lst_init(t_sect *tsect)
{
	tsect->segname = NULL;
	tsect->sectname = NULL;
	tsect->nsym = 0;
	tsect->sym = 0;
	tsect->next = NULL;
}

void lst_add(t_sect *tsect,char *seg, char *sect)
{
	t_sect *tmp;
	t_sect *new;
	static int i = 0;


	tmp = tsect;
	while(tmp->next != NULL)
		tmp = tmp->next;
	new = malloc(sizeof(t_sect));
	new->segname = seg;
	new->sectname = sect;
	new->nsym = i++;
	new->next = NULL;
	fill_sym(new);
	tmp->next = new;
	
}
