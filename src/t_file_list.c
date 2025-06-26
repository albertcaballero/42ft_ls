
#include "../ft_ls.h"
#include <stdlib.h>

void find_subdirs(t_file *list, int depth){
    DIR* FD;
    struct dirent* infile;
    t_file *tmp;

    if (!S_ISDIR(list->stats.st_mode))
        return;
    if (list->subdir)
        return;
    FD = opendir(list->path);
    if (!FD){
        ft_dprintf(2, "Error opening directory %s\n", list->name);
        return;
    }
    while ((infile = readdir(FD))) {
        if (!ft_strncmp (infile->d_name, ".", 2) || !strncmp (infile->d_name, "..", 3))
            continue;
        tmp = append_file(&list->subdir, list->path, infile->d_name);
        if (S_ISDIR(tmp->stats.st_mode) && depth == 1){
            find_subdirs(tmp, depth);
        }
    }
    closedir(FD);
}

t_file* append_file(t_file **head, char *path, char *name){
    t_file* newfile;
    t_file* temp = *head;
    while (temp && temp->next){
        temp = temp->next;
    }
    newfile = malloc(sizeof(t_file));
    fill_file(path, name, newfile);
    if (!temp)
        *head = newfile;
    else
        temp->next = newfile;
    return newfile;
}

void get_file_path(char parent[PATH_MAX], char *name, char path[PATH_MAX]){
    int i = 0;

    ft_strlcpy(path, parent, PATH_MAX);
    i = ft_strlen(path) - 1;
    if (path[i] != '/')
        ft_strlcat(path, "/", PATH_MAX);
    ft_strlcat(path, name, PATH_MAX);
}

void fill_file(char *path, char *name, t_file *file){
	struct stat statbuf;
    if (!file)
        return;

    file->name = ft_strdup(name);
    ft_strlcpy(file->path, path, PATH_MAX);
    if (file->path[ft_strlen(file->path) -1] != '/' && ft_strlen(file->path) > 0)
        ft_strlcat(file->path, "/", PATH_MAX);
    ft_strlcat(file->path, file->name, PATH_MAX);
    if (lstat(file->path, &statbuf) == -1){
        ft_dprintf(2, "ft_ls: cannot access '%s': No such file or dir\n", file->name);
        return;
    }
    file->stats = statbuf;
    file->subdir = NULL;
    file->next = NULL;
    file->hidden = file->name[0] == '.' && ft_strlen(file->name) > 1;
}
