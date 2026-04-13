
#include "../ft_ls.h"


void print_list(t_file *lst){
	for (;lst!=NULL;lst=lst->next){
		ft_dprintf(1, "%s,\n",lst->name);
	}
}

void print_stats(struct stat buf){
(void) buf;
}

size_t file_list_size(t_file *lst){
    size_t i = 0;
	for (;lst!=NULL;lst=lst->next){
        ++i;
    }
    return i;
}
