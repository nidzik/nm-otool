/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:56:30 by nidzik            #+#    #+#             */
/*   Updated: 2017/04/24 16:56:32 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char	*uint8tochar(uint8_t c)
{
	char *str;
	char *ret;

	ret = malloc(sizeof(char) * 3);
	str = "0123456789abcdef";
	ret[0] = (str[(c / 16) % 16]);
	ret[1] = (str[c % 16]);
	ret[2] = '\0';
	return (ret);
}

char	*inttobyte(int c)
{
	char *str;
	char *ret;

	ret = malloc(sizeof(char) * 3);
	str = "0123456789abcdef";
	ret[0] = (str[(c / 16) % 16]);
	ret[1] = (str[c % 16]);
	ret[2] = '\0';
	return (ret);
}

int		init_handle_32(int ac, t_cmds32 *c, t_sect *tsect, void *ptr)
{
	tsect->ac = ac;
	tsect->fat = 0;
	c->header = (struct mach_header *)ptr;
	c->ncmds = c->header->ncmds;
	c->lc = (void *)ptr + sizeof(*(c->header));
	return (0);
}

void	init_atoi(t_atoi *a)
{
	a->hex = (char *)malloc(sizeof(char) * 17);
	a->i = 15;
	a->check = 0;
}

int		breaak(char mask, t_env *e)
{
	if (mask == N_INDR)
		e->sym = 'I';
	else if (mask == N_ABS)
		e->sym = 'A';
	else if ((int)(e->array[e->i].n_sect) == 0)
	{
		e->sym = 'U';
		if (e->array[e->i].n_value != 0)
			e->sym = 'C';
	}
	else
		return (1);
	return (0);
}
