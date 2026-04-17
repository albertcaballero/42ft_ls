
#include "../ft_ls.h"

bool compare_name(char *a, char *b){

}

bool compare_time(struct tm *a, struct tm *b){

}


t_file *sort_list(t_file *orig, int flags){
    //TODO todo esto fuera
    // do a Merge sort for linked lists
    // call compare_name or compare_time depending on options
    // if -r just negate result
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
