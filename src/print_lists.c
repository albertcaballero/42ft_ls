#include "../ft_ls.h"

void print_entry(t_file *file, int flags, t_colwidth widths){
    if (LS_HIDDEN(file->hidden))
        return;
    if (flags & F_LONG)
        list_file_all(file, widths);
    else
        ft_dprintf(1, "%s  ", file->name);
}

void list_all(t_file *list, int flags, int depth){
    int len = file_list_size(list);
    if (depth > 1 && !(flags & F_RECURS))
        return;

    list = sort_list(list, flags);
    t_file *tmp = list;
    t_colwidth widths = get_col_widths(tmp);
    while (tmp ){ //print everything
        if (!S_ISDIR(tmp->stats.st_mode) && depth == 0){
            print_entry(tmp, flags, widths);
        } else if (depth != 0)
            print_entry(tmp, flags, widths);
        tmp = tmp->next;
    }
    if (depth != 0)
        ft_dprintf(1, "\n");
    if (depth != 0 && !(flags & F_RECURS)){
        free_file_list(list);
        return;
    }
    tmp = list;
    for (;list!=NULL; list=list->next){
        if (S_ISDIR(list->stats.st_mode)){
            if ((LS_ISDOTDIR(list->name) || LS_ISPARENTDIR(list->name)) && depth != 0)
                continue;
            if (LS_HIDDEN(list->hidden) && depth != 0)
                continue;
            if (depth != 0 || len > 1)
                ft_dprintf(1, "\n");
            if (len > 1 || (depth == 0 && flags & F_RECURS))
                ft_dprintf(1, "%s:\n", list->path);
            // if (!LS_ISDOTDIR(list->name))
            if (find_subdirs(list, flags & F_RECURS) == -1)
                continue;
            list_all(list->subdir, flags, depth + 1);
        }
    }
    free_file_list(tmp);
}
