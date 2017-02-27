/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:54:14 by nidzik            #+#    #+#             */
/*   Updated: 2017/02/27 22:37:25 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void cmp_segtxt(t_sect *sect)
{
	//ft_putendl(sect->sectname);
	//ft_putendl(SECT_TEXT);
	if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
        sect->sym = 'T';
	else
		sect->sym = 'S';
}

void cmp_segdata(t_sect *sect)
{
	if (ft_strcmp(sect->sectname, SECT_BSS) == 0)
        sect->sym = 'B';
	else if (ft_strcmp(sect->sectname, SECT_DATA) == 0)
        sect->sym = 'D';
    //else if (ft_strcmp(sect->sectname, SECT_COMMON) == 0)
	// sect->sym = 'C';
	else
		sect->sym = 'S';
}

void fill_sym(t_sect *sect)
{
	ft_putendl(sect->segname);
	if (ft_strcmp(sect->segname, SEG_TEXT) == 0)
			cmp_segtxt(sect);
	else if (ft_strcmp(sect->segname, SEG_DATA) == 0)
		cmp_segdata(sect);
	else if (ft_strcmp(sect->segname, SEG_OBJC) == 0)
        sect->sym = 'S';
//	else if (sect->lib == 1)
	//{
		//cmp_segdata(sect);
//		cmp_segtxt(sect);
	//}
	else
		sect->sym = 'U';
}

void lst_init(t_sect *tsect)
{
	tsect->segname = NULL;
	tsect->sectname = NULL;
	tsect->nsym = 0;
	tsect->sym = 0;
	tsect->fat = 0;
	tsect->lib = 0;
	tsect->next = NULL;
}

void lst_add(t_sect *tsect,char *seg, char *sect, int i)
{
	t_sect *tmp;
	t_sect *new;
	static int j = 0;
	(void)i;

	tmp = tsect;
	while(tmp->next != NULL)
		tmp = tmp->next;
	new = malloc(sizeof(t_sect));
	new->segname = seg;
	new->sectname = sect;
	if (j == 0 && ft_strcmp(seg, SEG_PAGEZERO) != 0)
		i++;
	new->nsym = i++;
	new->next = NULL;
	fill_sym(new);
//	printf("%s  %s  %c  %d\n",new->segname,new->sectname, new->sym, new->nsym);fflush(stdout);
	tmp->next = new;

}
