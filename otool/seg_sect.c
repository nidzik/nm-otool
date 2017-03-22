/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg_sect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 17:39:38 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/22 15:19:13 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void test(t_sect *tsect)
{
	while (tsect != NULL)
	{
		printf("%p ",tsect);fflush(stdout);
		printf("%p ",tsect->next);fflush(stdout);
		ft_putendl(tsect->sectname);
		tsect = tsect->next;
	}
}

t_sect *get_sect(void *ptr,int nbsect,t_sect *tsect,char *segname)
{
	struct section_64 *sect;
	int i = 0;
	char *str;
	str="0123456789abcdef";
	(void)segname;
	i = 0;
	sect = (struct section_64 *)ptr;
	if (nbsect == 0)
	{
//		lst_add(tsect,(char*)segname,"",0);
		return (tsect);
	}
	while (nbsect > 0)
	{
//		lst_add(tsect,(char*)segname,sect->sectname,i++);
//		if (ft_strcmp(sect->segname, SEG_TEXT) == 0 )

		if (sect != NULL)
			ft_putendl(sect->segname);
		if( ft_strcmp(sect->segname, SEG_TEXT) == 0 && ft_strcmp(sect->sectname, SECT_TEXT) == 0)
		{
			ft_putchar(str[((uint32_t)sect/ 16) % 16]);
			ft_putchar(str[(uint32_t)sect % 16]);
			ft_putchar('g');
			printf("%08x-",(unsigned char )(struct segment_command_64 *)ptr->vmaddr  );fflush(stdout);
		}
			else 
			{
							ft_putchar('n');
//				sect = NULL;
			}
			sect = (void *)sect + sizeof(*(sect));
		nbsect--;
	}
	return (tsect);
}


t_sect *get_seg_table(void *ptr_seg, t_sect *tsect, void *ptr)
{
	struct segment_command_64 *seg;

	seg = ( struct segment_command_64 *) ptr_seg;
	(void)ptr;
	get_sect((void *) ptr_seg  + sizeof(*(seg)),seg->nsects, tsect, seg->segname);
	return(tsect);
}
