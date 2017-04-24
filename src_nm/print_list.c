/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:56:18 by nidzik            #+#    #+#             */
/*   Updated: 2017/04/24 16:56:21 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_maillon(t_res *op)
{
	ft_putstr(op->off);
	ft_putchar(' ');
	ft_putchar(op->sym);
	ft_putchar(' ');
	ft_putendl(op->name);
}

void	print_list(t_res *op)
{
	sort(op);
	while (op->prev != NULL)
		op = op->prev;
	while (op != NULL)
	{
		if (op->next != NULL && ft_strcmp(op->next->name, op->name) == 0 &&\
			op->sym == 'I')
		{
			print_maillon(op->next);
			print_maillon(op);
			op = op->next->next;
		}
		else
		{
			print_maillon(op);
			op = op->next;
		}
	}
}
