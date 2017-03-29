#include "nm.h"

void addbegin(t_res *op)
{
	t_res *tmp;

	if (op->next->next != NULL)
		op->next->next->prev = op;
	op->next->prev = op->prev;
	tmp = op->next->next;
	op->next->next = op;
	op->prev = op->next;
	op->next = tmp;
}

void addinter(t_res *op)
{
    t_res *tmp;

	if (op->next->next != NULL)
        op->next->next->prev = op;
	op->prev->next = op->next;
    op->next->prev = op->prev;
    tmp = op->next->next;
    op->next->next = op;
    op->prev = op->next;
    op->next = tmp;
}

void sort(t_res *op)
{
	while (op->next != NULL)
		{
			while (ft_strcmp(op->name, op->next->name) > 0)
				{
					if (op->prev == NULL)
						addbegin(op);
					else
					addinter(op);
					if(op->prev != NULL && op->next && ft_strcmp(op->name, op->next->name) > 0)
						op = op->prev;
					else
						{
							while (op->prev != NULL)
								op = op->prev;
						}
				}
			
				op = op->next;
		}

}

t_res *add(t_res *op,char *name, char *off, char sym)
{
	t_res *tmp;
	t_res *new;

	if (op == NULL)
		{
			op = init(op, name, off, sym);
			return (op);
		}
	tmp = op;
	while(tmp->next != NULL)
		tmp = tmp->next;
	new = malloc(sizeof(t_res));
	new->name = name;
	new->off = off;
	new->sym = sym;
	new->prev = tmp;
	new->next = NULL;
	tmp->next = new;
	return (op);
}

t_res *init(t_res *op, char *name, char *off, char sym)
{
	op = malloc(sizeof(t_res));
	op->name = name;
	op->off = off;
	op->sym = sym;
	op->prev = NULL;
	op->next = NULL;
	return op;
}
