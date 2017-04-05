/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg_sect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 17:39:38 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/31 16:08:39 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_sect	*get_sect(void *ptr, int nbsect, t_sect *tsect, char *segname)
{
	struct section_64	*sect;
	int					i;

	i = 0;
	sect = (struct section_64 *)ptr;
	if (nbsect == 0)
	{
		lst_add(tsect, (char*)segname, "", 0);
		return (tsect);
	}
	while (nbsect > 0)
	{
//		printf("%u", sect->reserved1);
		if (sect->reserved1 != 0)
			tsect->ac = 100;
		lst_add(tsect, (char*)segname, sect->sectname, i++);
		sect = (void *)sect + sizeof(*(sect));
		nbsect--;
	}
	return (tsect);
}

t_sect	*get_seg_table(void *ptr_seg, t_sect *tsect)
{
	struct segment_command_64 *seg;

	seg = (struct segment_command_64 *)ptr_seg;
	get_sect((void *)ptr_seg + sizeof(*(seg)), seg->nsects, \
			tsect, seg->segname);
	return (tsect);
}
