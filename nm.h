/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 11:55:25 by nidzik            #+#    #+#             */
/*   Updated: 2017/02/27 22:31:55 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef NM_H
#define NM_H

#include "libft/libft.h"
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ar.h>
#include <mach-o/ranlib.h>

#define FLAGS_PROT PROT_READ | PROT_WRITE
#define FLAGS_MAP MAP_PRIVATE
#define FLAGS 0,FLAGS_PROT ,FLAGS_MAP, -1, 0


#define DEBUG ft_putchar('a');


typedef struct			s_cmds32
{
	int ncmds;

	struct mach_header	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
}						t_cmds32;

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
	int 	fat;
	int		lib;
	char	*namebin;
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

typedef struct			s_env
{
	char 				sym;
	t_sect				*tmp;
	int					i;
	char				*stringtable;
	struct nlist_64 	*array;
	struct nlist	 	*array32;
	t_res				*res;
}						t_env;

int			nm_type(void* ptr, int l, char *name);
void 		handle_32(void *ptr, int l, char *name);
void		handle_64(void *ptr, int l, char *name);
void		handle_fat(void *ptr);
void 		handle_lib(char *ptr, char *namelib);
char		*ft_itoa_base(unsigned long long int nb, int base);
t_sect		*get_seg_table(void *ptr_seg, t_sect *tsect);
t_sect		*get_seg_table_32(void *ptr_seg, t_sect *tsect);

void		lst_init(t_sect *tsect);
void		lst_add(t_sect *tsect,char *seg, char *sect, int i);
t_res		*init(t_res *op, char *name, char * off, char sym);
t_res		*add(t_res *op,char *name, char *off, char sym);
void		sort(t_res *op);
void		print_list(t_res *op);

void		print_bit_uint8_t(uint8_t ptr);
void		print_byte_uint8_t(uint8_t c);
char		*ft_atoi_hex(void *ptr, char c);
char		*ft_atoi_hex_32(unsigned int ptr, char c);
char		*ft_atoi_hex_fat(unsigned int ptr);

char		*uint8tochar(uint8_t c);
char		*inttobyte(int c);

void    print_output_64(t_cmds *c, void *ptr, t_sect *tsect);
t_env*	init_env(t_env *e, void *ptr, int symoff, int stroff);
#endif

