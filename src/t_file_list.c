
#include "../ft_ls.h"

void find_subdirs(t_file *list){
    for (;list!=NULL; list=list->next){
        if (S_ISDIR(list->stats.st_mode))
            ;
    }

}

t_file *add_file(char *path, char *name){
    t_file *newfile = malloc(sizeof(t_file));
	struct stat statbuf;
    if (!newfile)
        return NULL;

    newfile->name = ft_strdup(name);
    ft_strlcpy(newfile->path, path, PATH_MAX);
    if (newfile->path[ft_strlen(newfile->path) -1] != '/')
        ft_strlcat(newfile->path, "/", PATH_MAX);
    ft_strlcat(newfile->path, newfile->name, PATH_MAX);
    lstat(newfile->path, &statbuf);
    newfile->stats = statbuf;
    newfile->subdir = NULL;
    newfile->next = NULL;

    return newfile;
}
