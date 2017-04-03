/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:44:03 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/04 19:07:07 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		t_atoi(const char *str)
{
	int r;
	int np;

	np = 1;
	r = 0;
	if (!(*str))
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		np = (*str == '-' ? -1 : 1);
		str++;
	}
	while (*str == '0')
		str++;
	while (ft_isdigit(*str))
	{
		r = r * 10 + (*str - 48);
		str++;
	}
	return (r * np);
}

void	print_library(void *ptr, struct ranlib *ran, \
						unsigned int n, char *namelib)
{
	unsigned int check_ran;

	(void)ptr;
	(void)namelib;
	check_ran = -1;
	while (n-- > 0)
	{
		if (((ran[n].ran_off != check_ran)) &&\
			!ft_strncmp(ptr + ran[n].ran_off, AR_EFMT1, ft_strlen(AR_EFMT1)))
		{
			ft_putchar('\n');
			ft_putstr(namelib);
			ft_putchar('(');
			ft_putstr(ptr + ran[n].ran_off + sizeof(struct ar_hdr));
			ft_putstr("):\n");
			nm_type((void *)ptr + ran[n].ran_off + sizeof(struct ar_hdr)
					+ t_atoi(ptr + ran[n].ran_off + 3), 1, "lib");
		}
		check_ran = ran[n].ran_off;
	}
}

void	sort_library(struct ranlib *ran, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;
	struct ranlib	temp;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - 1)
		{
			while (ran[j].ran_off < ran[j + 1].ran_off)
			{
				temp = ran[j + 1];
				ran[j + 1] = ran[j];
				ran[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	handle_lib(char *ptr, char *namelib)
{
	int				hdr_sz;
	unsigned int	i;
	struct ranlib	*ran;
	t_sect			*tsect;

	tsect = malloc(sizeof(t_sect));
	lst_init(tsect);
	tsect->lib = 1;
	hdr_sz = 0;
	if (ft_strcmp(ptr + SARMAG + sizeof(struct ar_hdr), SYMDEF) &&
		ft_strcmp(ptr + SARMAG + sizeof(struct ar_hdr), SYMDEF_SORTED))
		return ;
	hdr_sz = t_atoi(ptr + SARMAG + ft_strlen(AR_EFMT1)) + \
		sizeof(struct ar_hdr) + SARMAG;
	i = *(int *)(ptr + hdr_sz) / sizeof(struct ranlib);
	ran = (struct ranlib *)malloc(sizeof(struct ranlib) * i);
	while (i-- > 0)
	{
		ran[i] = *(struct ranlib *)(ptr + hdr_sz + 4 + i * \
									(sizeof(struct ranlib)));
	}
	i = *(int *)(ptr + hdr_sz) / sizeof(struct ranlib);
	sort_library(ran, i);
	print_library(ptr, ran, i, namelib);
	free(ran);
}
