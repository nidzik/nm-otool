/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_otool_lib.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 18:42:55 by jwalle            #+#    #+#             */
/*   Updated: 2016/10/29 18:44:05 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int t_atoi(const char *str)
{
    int r;
    int np;

    np = 1;
    r = 0;
    if (!(*str))
        return (0);
    while (*str == ' ' || *str == '\t' || *str == '\n'
           || *str == '\v' || *str == '\r' || *str == \
'\f')
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


void		print_library(void *ptr, struct ranlib *ran,
	unsigned int n, t_otool_env *e)
{
	printf("Archive : %s\n", e->file);
	while (n-- > 0)
	{
		if ((ran[n].ran_off != ran[n + 1].ran_off) &&
			!ft_strncmp(ptr + ran[n].ran_off, AR_EFMT1, ft_strlen(AR_EFMT1)))
		{
			printf("%s(%s):\n", e->file, ptr + ran[n].ran_off + AR_HDR_SIZE);
			ft_otool(ptr + ran[n].ran_off + AR_HDR_SIZE
				+ t_atoi(ptr + ran[n].ran_off + 3), e);
		}
	}
}

void		sort_library(struct ranlib *ran, unsigned int n)
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

void		handle_otool_library(char *ptr, t_otool_env *e)
{
	int					hdr_sz;
	unsigned int		i;
	struct ranlib		*ran;

	e->lib = 1;
	if (ft_strcmp(ptr + SARMAG + AR_HDR_SIZE, SYMDEF) &&
		ft_strcmp(ptr + SARMAG + AR_HDR_SIZE, SYMDEF_SORTED))
		return ;
	hdr_sz = t_atoi(ptr + SARMAG + ft_strlen(AR_EFMT1)) + AR_HDR_SIZE + SARMAG;
	i = *(int *)(ptr + hdr_sz) / sizeof(struct ranlib);
	ran = (struct ranlib *)malloc(RAN_SIZE * i);
	while (i-- > 0)
		ran[i] = *(struct ranlib *)(ptr + hdr_sz + 4 + i * (RAN_SIZE));
	i = *(int *)(ptr + hdr_sz) / sizeof(struct ranlib);
	sort_library(ran, i);
	print_library(ptr, ran, i, e);
}
