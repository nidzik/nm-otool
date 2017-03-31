/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 20:36:26 by nidzik            #+#    #+#             */
/*   Updated: 2017/03/04 16:01:06 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

#define ARCH "!<arch>\n"

int  nm_type(void* ptr, int l, char *name)
{
	int magic_number;
	char *magic_string;

	magic_number = *(int *)ptr;
	magic_string = (char *)ptr;
	if (magic_number == (int)MH_MAGIC_64 && l == 1)
		handle_64(ptr,1, name);
	else if (magic_number == (int)MH_MAGIC_64 && (l == 0 || l == 2))
			handle_64(ptr,0, name);
	else if (magic_number == (int)MH_MAGIC && l == 1)
		handle_32(ptr, 1, name);
	else if (magic_number == (int)MH_MAGIC && l == 0)
		handle_32(ptr, 0, name);
	else if (ft_strncmp(magic_string, ARCH,8) == 0)
		handle_lib((char *)ptr, name);
	else
		{
			magic_number = *((int *)((void *)ptr + 4096));
			if (magic_number == (int)MH_MAGIC_64)
				handle_64(ptr + 4096, 0, name);
			else
				handle_fat((void *)ptr);
        }
	return (1);
}

int mmap_file(int fd, char *name)
{
	void 		*ptr;
	struct stat buf;

	ptr = NULL;
	if (fstat(fd, &buf) < 0)
		return (-1);
	if ((ptr = mmap(0,buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (-1);
	nm_type(ptr, 0, name);
	if (munmap(ptr, buf.st_size) < 0)
		return (-1);
	return (0);
}

int main(int ac, char **av)
{
	int fd;
	(void)ac;
	av++;
	if (ac == 1)
		{
			if ((fd = open("a.out",O_RDONLY)) == -1)
				{
					ft_putstr("Error when openning the file");
					return (0);
				}
			else
					mmap_file(fd,"a.out");
		}
	else
		while (*av)
			{
				if ((fd = open(*av,O_RDONLY)) == -1)
					{
						ft_putstr("Error when openning the file");
						return (0);
					}
				else
					{
						if (mmap_file(fd, *av) == -1)
							{
								ft_putendl("fail in mmap_file");
								return (-1);
							}
					}
				av++;
			}
	return (0);
}

