#include "../ft_ls.h"

void list_dir(const char *dir){
    (void) dir;
}

void list_file_all(t_file *file){
    // struct tm tm;
    ft_dprintf(1, "%c%s %i %s %s %i %s %s\n",
            'a',"permissions",
            file->stats.st_nlink,
            "user","group",
            file->stats.st_size,
            "mod date", //file->stats.st_mtim,
            file->name);
}

void print_entry(t_file *file, int flags){
    if (flags & F_LONG)
        list_file_all(file);
    else
        ft_dprintf(1, "%s  ", file->name);
}

void list_all(t_file *list, int flags){
    //list = sort_list(&list, flags);
    for (;list!=NULL; list=list->next){
        if (S_ISDIR(list->stats.st_mode)){
            find_subdirs(list);
        }
        if (flags & F_RECURS){
        }
        print_entry(list, flags);

    }
    ft_dprintf(1, "\n");
}
