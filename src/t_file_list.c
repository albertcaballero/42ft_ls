
#include "../ft_ls.h"
#include <stdlib.h>

void find_subdirs(t_file *list){
    DIR* FD;
    struct dirent* infile;
    t_file *newfile = NULL;
    t_file *head = NULL;

    for (;list!=NULL; list=list->next){
        if (S_ISDIR(list->stats.st_mode)){
            FD = opendir(list->path);
            if (!FD){
                ft_dprintf(2, "Error opening directory %s\n", list->name);
                return;
            }
            head = malloc(sizeof(t_file));
            list->subdir = head;
            while ((infile = readdir(FD))) {
                if (!ft_strncmp (infile->d_name, ".", 2) || !strncmp (infile->d_name, "..", 3))
                    continue;
                add_file(list->path, infile->d_name, head);
                if (S_ISDIR(list->subdir->stats.st_mode)){
                    find_subdirs(head);
                }
                newfile = malloc(sizeof(t_file));
                head->next = newfile;
            }
            free(newfile);
            head->next = NULL;
            closedir(FD);
        };
    }
}

void add_file(char *path, char *name, t_file *file){
	struct stat statbuf;
    if (!file)
        return;

    file->name = ft_strdup(name);
    ft_strlcpy(file->path, path, PATH_MAX);
    if (file->path[ft_strlen(file->path) -1] != '/')
        ft_strlcat(file->path, "/", PATH_MAX);
    ft_strlcat(file->path, file->name, PATH_MAX);
    lstat(file->path, &statbuf);
    file->stats = statbuf;
    file->subdir = NULL;
    file->next = NULL;
}
