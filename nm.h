/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 11:55:25 by nidzik            #+#    #+#             */
/*   Updated: 2017/02/24 21:46:37 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef NM_H
#define NM_H

#include "libft/libft.h"
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FLAGS_PROT PROT_READ | PROT_WRITE
#define FLAGS_MAP MAP_PRIVATE
#define FLAGS 0,FLAGS_PROT ,FLAGS_MAP, -1, 0




typedef struct			s_cmds
{
	int ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
}						t_cmds;

typedef struct			s_sect
{
	int		nbsect;
	char 	*segname;
	char	*sectname;

	char	sym;
	int		nsym;
	struct s_sect *next;
	
}						t_sect;

typedef struct          s_res
{
	char			*off;
	char			sym;
	char			*name;
    struct s_res 	*prev;
    struct s_res 	*next;
}						t_res;

void 		handle_32(void *ptr);
void		handle_64(void *ptr);
char		*ft_itoa_base(unsigned long long int nb, int base);
t_sect		*get_seg_table(void *ptr_seg, t_sect *tsect);

void		lst_init(t_sect *tsect);
void		lst_add(t_sect *tsect,char *seg, char *sect);
t_res		*init(t_res *op, char *name, char * off, char sym);
t_res		*add(t_res *op,char *name, char *off, char sym);
void		sort(t_res *op);
void		print_list(t_res *op);

void		print_bit_uint8_t(uint8_t ptr);
void		print_byte_uint8_t(uint8_t c);
char		*ft_atoi_hex(void *ptr);

char		*uint8tochar(uint8_t c);
char		*inttobyte(int c);

#endif

