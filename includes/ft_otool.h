/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:00:10 by nidzik            #+#    #+#             */
/*   Updated: 2017/04/24 17:00:12 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include <fcntl.h>
# include <grp.h>
# include <time.h>
# include "../libft/libft.h"

# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <ar.h>

# define MH_RANLIB 0x72613c21
# define AR_HDR_SIZE sizeof(struct ar_hdr)
# define RAN_SIZE sizeof(struct ranlib)

typedef	struct		s_otool_env
{
	int				fat;
	int				dylink;
	int				cpu;
	int				lib;
	int				dylib;
	int				obj;
	int				bundle;
	char			*file;

}					t_otool_env;

char				*ft_itoa_base(int nb, int base);
void				print_otool(uint32_t size, uint32_t addr, char *offset,
					t_otool_env *e);
void				handle_otool_library(char *ptr, t_otool_env *e);
void				handle_otool_64(char *ptr, t_otool_env *e);
void				handle_otool_32(char *ptr, t_otool_env *e);
void				handle_otool_fat(char *ptr, t_otool_env *e);
void				handle_otool_taf(char *ptr, t_otool_env *e);
void				ft_otool(char *ptr, t_otool_env *e);

#endif
