/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_res.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 21:40:43 by nidzik            #+#    #+#             */
/*   Updated: 2017/02/24 23:10:37 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void lst_sort(t_res *res)
{
	t_res *tmp;

	tmp = res;
	while (tmp->next != NULL)
	{
		;
	}
}

void lst_res_add_name(t_res *res, char *name)
{
	t_res *tmp;
	t_res *new;
	t_res *prev = NULL;

	tmp = res;
	while(tmp->next != NULL)
	{
		prev = NULL;
		tmp = tmp->next;
		prev = tmp;
	}
	new = malloc(sizeof(t_res));
	new->name = name;
	new->prev = prev;
	new->next = NULL;
	tmp->next = new;

}
