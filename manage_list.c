/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:54:14 by nidzik            #+#    #+#             */
/*   Updated: 2017/02/20 16:42:55 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void fill_sym(t_sect *sect)
{
	if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
		sect->sym = 'T';
	else if (ft_strcmp(sect->sectname, SECT_DATA) == 0)
        sect->sym = 'b';
	else if (ft_strcmp(sect->sectname, SECT_COMMON) == 0)
        sect->sym = 'C';
	else if (ft_strcmp(sect->sectname,SECT_TEXT) == 0)
        sect->sym = 'T';
	else if (ft_strcmp(sect->sectname,SECT_TEXT) == 0)
        sect->sym = 'T';
	else if (ft_strcmp(sect->sectname,SECT_TEXT) == 0)
        sect->sym = 'T';
	else if (ft_strcmp(sect->sectname,SECT_TEXT) == 0)
        sect->sym = 'T';
}

void lst_init(t_sect *tsect)
{
	tsect->segname = NULL;
	tsect->sectname = NULL;
	tsect->nsym = 0;
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
