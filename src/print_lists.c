#include "../ft_ls.h"

void print_entry(t_file *file, int flags){
    if (file->hidden && !(flags & F_ALL))
        return;
    if (flags & F_LONG)
        list_file_all(file);
    else
        ft_dprintf(1, "%s  ", file->name);
}



void list_all(t_file *list, int flags, int depth){
    int len = file_list_size(list);
    t_file *tmp = list;
    if (depth > 1 && !(flags & F_RECURS))
        return;
    //list = sort_list(list);
    while (tmp){
        if (!S_ISDIR(tmp->stats.st_mode) || depth != 0){
            print_entry(tmp, flags);
        }
        tmp = tmp->next;
    }
    ft_dprintf(1, "\n");
    for (;list!=NULL; list=list->next){
        if (S_ISDIR(list->stats.st_mode) && (depth == 0 || flags & F_RECURS)){
            if (len > 1)
                ft_dprintf(1, "\n%s:\n", list->path);
            find_subdirs(list, flags & F_RECURS);
            list_all(list->subdir, flags, depth + 1);
            //free_entry(list) //por si haces "ft_ls -R /"
        }
    }
    ft_dprintf(1, "\n");
}
