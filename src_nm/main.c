/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 20:36:26 by nidzik            #+#    #+#             */
/*   Updated: 2018/04/01 22:29:05 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

#define ARCH "!<arch>\n"
#define MN "magic_number"

int	nm_type_next(int magic_number, void *ptr, t_relou name, int l)
{
	int		ac;
	char	*magic_string;

	magic_string = (char *)ptr;
	ac = 2;
	if (magic_number == (int)MH_MAGIC_64 && l == 1)
		handle_64(ptr, 1, name, ac);
	else if (magic_number == (int)MH_MAGIC_64 && (l == 0 || l == 2))
		handle_64(ptr, 0, name, ac);
	else if (magic_number == (int)MH_MAGIC && l == 1)
		handle_32(ptr, 1, name.name, ac);
	else if (magic_number == (int)MH_MAGIC && l == 0)
		handle_32(ptr, 0, name.name, ac);
	else if (ft_strncmp(magic_string, ARCH, 8) == 0)
		handle_lib((char *)ptr, name.name, ac);
	else
		return (1);
	return (0);
}

int	nm_type(void *ptr, int l, t_relou name, int ac)
{
	int		magic_number;
	char	*magic_string;

	magic_number = *(int *)ptr;
	magic_string = (char *)ptr;
	if (magic_number == (int)MH_MAGIC_64 || magic_number == (int)MH_MAGIC ||\
		ft_strncmp(magic_string, ARCH, 8) == 0 ||\
		magic_number == (int)swap_little_big(FAT_MAGIC))
	{
		if (nm_type_next(magic_number, ptr, name, l) == 1)
		{
			magic_number = *((int *)((void *)ptr + 4096));
			if (magic_number == (int)MH_MAGIC_64)
				handle_64(ptr + 4096, 0, name, ac);
			else
				handle_fat((void *)ptr, ac, name);
		}
	}
	return (1);
}

int	mmap_file(int fd, char *name, int args)
{
	void		*ptr;
	struct stat buf;
	t_relou n;
	
	ptr = NULL;
	if (fstat(fd, &buf) < 0)
		return (-1);
	if ((ptr = mmap(0, buf.st_size, PROT_READ,\
					MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		return (-1);
	}
	n.name = name;
	n.sizefile = (int)buf.st_size;
	nm_type(ptr, 0, n, args);
	if (munmap(ptr, buf.st_size) < 0)
		return (-1);
	return (0);
}

int	boucle_main(char **av, int fd, int ac)
{
	while (*av)
	{
		if (ac > 2)
		{
			ft_putchar('\n');
			ft_putstr(*av);
			ft_putendl(":");
		}
		if ((fd = open(*av, O_RDONLY)) == -1 ||\
			ft_strcmp(*av, "/usr/bin/audiodevice") == 0)
		{
			ft_putstr("ft_nm: ");
			ft_putstr(*av);
			ft_putendl(": No such file or directory.");
			return (-1);
		}
		else if (mmap_file(fd, *av, ac) == -1)
		{
			ft_putendl("fail in mmap_file");
			return (-1);
		}
		av++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int fd;

	fd = 0;
	av++;
	if (ac == 1)
	{
		if ((fd = open("a.out", O_RDONLY)) == -1)
		{
			ft_putstr("ft_nm: a.out: No such file or directory.");
			return (-1);
		}
		else
			mmap_file(fd, "a.out", ac);
	}
	else
		boucle_main(av, fd, ac);
	return (0);
}
