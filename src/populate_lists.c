#include "ft_ls.h"

void check_filetype(t_file *lst){
	struct stat statbuf;
	for (;lst;lst = lst->next){
		stat(lst->name, &statbuf);

	}

}
