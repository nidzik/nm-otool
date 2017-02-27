/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 20:36:26 by nidzik            #+#    #+#             */
/*   Updated: 2017/02/27 19:16:40 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

#define ARCH "!<arch>\n"

void nm_type(void* ptr)
{
	int magic_number;
	char *magic_string;

	magic_number = *(int *)ptr;
	magic_string = (char *)ptr;
	if (magic_number == (int)MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == (int)MH_MAGIC)
		handle_32(ptr);
	else if (ft_strncmp(magic_string, ARCH,8) == 0)
		handle_lib((char *)ptr);
	//else 
	//handle_fat((void *)ptr + 4096);

}

int mmap_file(int fd)
{
	void 		*ptr;
	struct stat buf;

	ptr = NULL;
	if (fstat(fd, &buf) < 0)
		return (-1);
	if ((ptr = mmap(0,buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (-1);
	nm_type(ptr);
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
				{
					mmap_file(fd);
				}
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
						if (mmap_file(fd) == -1)
							{
								ft_putendl("fail in mmap_file");
								return (-1);
							}
					}
				av++;
			}


        
	return (0);
}

