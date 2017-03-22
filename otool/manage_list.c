/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:54:14 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/04 16:00:43 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void cmp_segtxt(t_sect *sect)
{
	if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
			sect->sym = 'T';
	else
		sect->sym = 'S';
}

void cmp_segdata(t_sect *sect)
{
	/* ft_putstr("D"); */
	/* ft_putendl(sect->segname); */
	/* ft_putendl(sect->sectname); */
	/* ft_putnbr(sect->lib); */
	//if (sect->lib == 1 && sect->segname != SEG_DATA)
	//	return;
	//	ft_putstr("true:");
	if (ft_strcmp(sect->sectname, SECT_BSS) == 0)
        sect->sym = 'B';
	else if (ft_strcmp(sect->sectname, SECT_DATA) == 0)
		{
        sect->sym = 'D';
		//ft_putendl("yes");
		}
    //else if (ft_strcmp(sect->sectname, SECT_COMMON) == 0)
	//		sect->sym = 'C';
	else
		sect->sym = 'S';
}

void fill_sym(t_sect *sect)
{
	//	ft_putendl(sect->segname);
	if (ft_strcmp(sect->segname, SEG_TEXT) == 0)
			cmp_segtxt(sect);
	else if (ft_strcmp(sect->segname, SEG_DATA) == 0)
		cmp_segdata(sect);
	else if (ft_strcmp(sect->segname, SEG_OBJC) == 0)
        sect->sym = 'S';
	else if (sect->lib == 1)
		{
			cmp_segtxt(sect);
			if (sect->sym != 'T')
				cmp_segdata(sect);
//					ft_putendl("lib");
		}
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
	tsect->namebin = NULL;
	tsect->next = NULL;
}

void lst_add(t_sect *tsect,char *seg, char *sect, int i)
{
	t_sect *tmp;
	t_sect *new;
	static int j = 0;
	int k;

	k = 0;
	tmp = tsect;
	while(tmp->next != NULL)
		tmp = tmp->next;
	new = malloc(sizeof(t_sect));
	new->segname = seg;
	new->sectname = sect;
	if (i == 0 && ft_strcmp(seg, SEG_PAGEZERO) != 0)
		{
			//					j++;

			i++;
			k++;
		}

	new->nsym = j++;
	if (tmp->lib == 1)
		{
			//					ft_putendl("oui");			
		new->lib = 1;
	new->nsym = tmp->nsym + 1;
		}
	new->next = NULL;
	fill_sym(new);
//				printf("%s  %s  %c  %d\n",new->segname,new->sectname, new->sym, new->nsym);fflush(stdout);
	tmp->next = new;

}
