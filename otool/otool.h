/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 07:48:56 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/22 13:15:22 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
#define OTOOL_H

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ar.h>
#include <mach-o/ranlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include "../libft/libft.h"

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


int			nm_type(void* ptr, int l, char *name);
void 		handle_32(void *ptr, int l, char *name);
void		handle_64(void *ptr, int l, char *name);
void		handle_fat(void *ptr);
void 		handle_lib(char *ptr, char *namelib);
t_sect		*get_seg_table(void *ptr_seg, t_sect *tsect, void *ptr);
t_sect		*get_seg_table_32(void *ptr_seg, t_sect *tsect);
char		*ft_atoi_hex(void *ptr, char c);
char		*ft_atoi_hex_32(unsigned int ptr, char c);
char		*ft_atoi_hex_fat(unsigned int ptr);
void		lst_init(t_sect *tsect);
void		print_list(t_res *op);
t_res		*add(t_res *op,char *name, char *off, char sym);
#endif
