#include "nm.h"


t_sect *get_sect(void *ptr,int nbsect,t_sect *tsect)
{
	struct section_64 *sect;
	int i;
	t_sect *save;

	if (nbsect == 0)
		return NULL;
	save = tsect;
		printf("\t \t \\o%s    %d   \n",save->segname,save->nbsect);fflush(stdout);
	i = 0;
	ft_putendl("\tget_sect:");
	sect = (struct section_64 *)ptr;
	while (nbsect >= 0)
		{
			tsect->sectname = malloc(sizeof(char) * 16);
			while(sect->sectname[i])
				{
					tsect->sectname[i] = sect->sectname[i];
					i++;
				}
			i = 0;
			//		fill_sym(tsect);
			ft_putchar('>');
			ft_putendl(sect->sectname);
			ft_putendl(tsect->sectname);
			nbsect--;
			printf("\t \t >>%s    %d   \n",tsect->segname,tsect->nbsect);fflush(stdout);
			//			printf("  offset section : %u   offset realloc entries %lu \n",sect->offset,sizeof(*(sect)));fflush(stdout);
			sect = (void *)sect + sizeof(*(sect));

			tsect = tsect->next;
			tsect = malloc(sizeof(tsect));
			tsect->segname = malloc(sizeof(char) * 16);
			//			tsect->segname = save->segname;
			tsect->nbsect = nbsect;
			tsect->next = NULL;
		}
		printf("\t \t \\o%s    %d    %s \n",save->segname,save->nbsect, save->sectname);fflush(stdout);
	return (save);
}
void fill_sym(t_sect *tsect)
{
	(void)tsect;
	;
}
t_sect *get_seg_table(void *ptr_seg, t_sect *tsect)
{
	struct segment_command_64 *seg;

	t_sect *save;
	int j;
	ft_putendl("\tget_seg_table:");
	save = tsect;	
	while (tsect != NULL)
		tsect = tsect->next;
	tsect = malloc(sizeof(tsect));
	if (save == NULL)
	save = tsect;
	
			seg = ( struct segment_command_64 *) ptr_seg;

	j = 0;

	tsect->segname = malloc(sizeof(char) * 16);
	            while(seg->segname[j] || j < 16)
                {
                    tsect->segname[j] = seg->segname[j];
                    j++;
                }
	ft_putstr(tsect->segname);
	tsect->nbsect = seg->nsects;
	//fill_sym(tsect);
	if (save)
		{
			printf("\t \t youpilou seg:%s  nbsect:%d   \n",save->segname,save->nbsect);fflush(stdout);
		}
	else
		{
		ft_putendl("Null");
	}
	save = get_sect((void *) ptr_seg  + sizeof(*(seg)),seg->nsects, tsect);
	//		tsect->next = NULL;
	return(save);
}
