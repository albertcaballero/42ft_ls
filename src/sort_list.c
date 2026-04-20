
#include "../ft_ls.h"

void filename_tolower(char *name) {
    for (int i = 0; name[i]; i++) {
        name[i] = ft_tolower(name[i]);
    }
}

int compare_files(t_file *a, t_file *b, int flags){
    int rev = !!(flags & F_REVERSE);
    //use ^rev to flip result if set (XOR)
    char path_a[PATH_MAX];
    char path_b[PATH_MAX];
    ft_strlcpy(path_a, a->path, PATH_MAX);
    ft_strlcpy(path_b, b->path, PATH_MAX);
    filename_tolower(path_a);
    filename_tolower(path_b);

    if (flags & F_TIME){
        if (a->stats.st_mtim.tv_sec != b->stats.st_mtim.tv_sec)
            return (a->stats.st_mtim.tv_sec > b->stats.st_mtim.tv_sec) ^ rev;
        if (a->stats.st_mtim.tv_nsec != b->stats.st_mtim.tv_nsec)
            return (a->stats.st_mtim.tv_nsec > b->stats.st_mtim.tv_nsec) ^ rev;
        return (ft_strncmp(path_a, path_b, ft_strlen(path_a) + 1) < 0) ^ rev;
    }else{
        return (ft_strncmp(path_a, path_b, ft_strlen(path_a) + 1) < 0) ^ rev;
    }
}

t_file *merge(t_file *first, t_file *second, int flags) {

    if (!first) return second;
    if (!second) return first;

    if (compare_files(first, second, flags)) {
        first->next = merge(first->next, second, flags);
        return first;
    }
    else {
        second->next = merge(first, second->next, flags);
        return second;
    }
}

t_file *split_list(t_file *head) {
    t_file *fast = head;
    t_file *slow = head;

    while (fast && fast->next) {
        fast = fast->next->next;
        if (fast) {
            slow = slow->next;
        }
    }

    t_file *temp = slow->next;
    slow->next = NULL;
    return temp;
}

t_file *sort_list(t_file *head, int flags){
    if (!head || !head->next)
        return head;

    t_file *second = split_list(head);

    head = sort_list(head, flags);
    second = sort_list(second, flags);

    return merge(head, second, flags);
}
