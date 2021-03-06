/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg_sect32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 17:39:34 by nidzik            #+#    #+#             */
/*   Updated: 2017/02/27 22:17:12 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_sect	*get_sect_32(void *ptr, int nbsect, t_sect *tsect, char *segname)
{
	struct section	*sect;
	int				i;

	i = 0;
	sect = (struct section *)ptr;
	if (nbsect == 0)
	{
		lst_add(tsect, (char*)segname, "", i);
		return (tsect);
	}
	while (nbsect > 0)
	{
		lst_add(tsect, (char*)segname, sect->sectname, i++);
		sect = (void *)sect + sizeof(*(sect));
		nbsect--;
	}
	return (tsect);
}

t_sect	*get_seg_table_32(void *ptr_seg, t_sect *tsect)
{
	struct segment_command	*seg;

	seg = (struct segment_command *)ptr_seg;
	get_sect_32((void *)ptr_seg + sizeof(*(seg)), seg->nsects, \
				tsect, seg->segname);
	return (tsect);
}
