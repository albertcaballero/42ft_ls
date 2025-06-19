#include "../ft_ls.h"

void list_dir(const char *dir){
    (void) dir;
}

void list_file_all(t_file *file){
    ft_dprintf(1, "%c%s %i %s %s %i %s %s\n", 
            'a',"permissions", 
            file->stats.st_nlink,
            "user","group",
            file->stats.st_size,
            "mod date", //file->stats.st_mtim,
            file->name);
}

void list_all(t_file *list, int flags){
    //list = sort_list(&list, flags);
    for (;list!=NULL; list=list->next){
        if (flags & F_RECURS){
           if (S_ISDIR(list->stats.st_mode))
               ;
        }

        if (flags & F_LONG)
            list_file_all(list);
        else
            ft_dprintf(1, "%s  ", list->name);
    }
    ft_dprintf(1, "\n");
}
