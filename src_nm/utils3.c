/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:56:50 by nidzik            #+#    #+#             */
/*   Updated: 2017/04/24 16:56:53 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

int		init_handle64(t_sect *tsect, t_cmds *c, void *ptr, int l)
{
	c->header = (struct mach_header_64 *)ptr;
	c->ncmds = c->header->ncmds;
	c->lc = (void *)ptr + sizeof(*(c->header));
	if (l == 1 || c->header->filetype == MH_OBJECT ||\
		c->header->filetype == MH_DYLIB || c->header->filetype == MH_BUNDLE)
		tsect->lib = 1;
	return (0);
}
