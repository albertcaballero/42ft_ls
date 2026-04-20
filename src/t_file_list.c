
#include "../ft_ls.h"
#include <stdlib.h>

//find directory files
int find_subdirs(t_file *list, int depth){
    DIR* FD;
    struct dirent* infile;
    (void)depth;

    if (!S_ISDIR(list->stats.st_mode))
        return -1;
    if (list->subdir)
        return -1;
    FD = opendir(list->path);
    if (!FD){
        ft_dprintf(2, "ft_ls: cannot open directory '%s': Permission denied\n", list->name);
        return -1;
    }
    // if (LS_ISDOTDIR(list->name) || LS_ISPARENTDIR(list->name))
    //     return 0;
    while ((infile = readdir(FD))) {
        //TODO check if hidden to improve performance
        append_file(&list->subdir, list->path, infile->d_name);
    }
    closedir(FD);
    return 0;
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
        file->name[0] = '\0';
        return;
    }
    file->stats = statbuf;
    file->subdir = NULL;
    file->next = NULL;
    file->hidden = file->name[0] == '.';
}

void free_file_list(t_file *list){
    t_file *fr = NULL;
    for (;list!=NULL; list=list->next){
        free_file(fr);
        fr = list;
    }
    free_file(fr);
}

void free_file(t_file *file){
    if (!file)
        return;

    if (file->name)
        free(file->name);
    free(file);
    file = NULL;
}
