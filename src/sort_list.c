
#include "../ft_ls.h"

t_file *sort_list(t_file *orig){
    t_file *newlist = NULL;
    t_file *head = NULL;
    t_file *tmp = orig;
    while (tmp){
        if (!S_ISDIR(orig->stats.st_mode)){
            if (!newlist){
                newlist = tmp;
                head = newlist;
            }
            else{
                newlist->next = tmp;
                newlist = newlist->next;
                newlist->next = NULL;
            }
        }
        tmp = tmp->next;
    }
    tmp = orig;
    while (tmp){
        if (S_ISDIR(orig->stats.st_mode)){
            if (!newlist){
                newlist = tmp;
                head = newlist;
            }
            else{
                newlist->next = tmp;
                newlist = newlist->next;
                newlist->next = NULL;
            }
        }
        tmp = tmp->next;
    }
    newlist->next = NULL;
    return head;
}
