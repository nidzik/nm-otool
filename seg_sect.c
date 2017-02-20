#include "nm.h"

void test(t_sect *tsect)
{
	while (tsect != NULL)
	{
		printf("%p ",tsect);fflush(stdout);
		printf("%p ",tsect->next);fflush(stdout);
		ft_putendl(tsect->sectname);
		tsect = tsect->next;
	}
}

t_sect *get_sect(void *ptr,int nbsect,t_sect *tsect,char *segname)
{
	struct section_64 *sect;
	
	sect = (struct section_64 *)ptr;
	if (nbsect == 0)
	{
		lst_add(tsect,(char*)segname,"");
		return (tsect);
	}
	while (nbsect > 0)
	{
		lst_add(tsect,(char*)segname,sect->sectname);
		sect = (void *)sect + sizeof(*(sect));
		nbsect--;
	}
	return (tsect);
}


t_sect *get_seg_table(void *ptr_seg, t_sect *tsect)
{
	struct segment_command_64 *seg;

	seg = ( struct segment_command_64 *) ptr_seg;
	get_sect((void *) ptr_seg  + sizeof(*(seg)),seg->nsects, tsect, seg->segname);
	return(tsect);
}
