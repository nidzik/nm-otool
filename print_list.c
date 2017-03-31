#include "nm.h"

void print_list(t_res *op)
{
    sort(op);
    while(op->prev != NULL)
        op = op->prev;
    while (op != NULL)
        {
            ft_putstr(op->off);
            ft_putchar(' ');
            ft_putchar(op->sym);
            ft_putchar(' ');
            ft_putendl(op->name);
            op = op->next;
        }
}
