#include "../ft_ls.h"

t_file* generate_list(char **argv){
	t_file *head=NULL;
	t_file* args=malloc(sizeof(t_file));
	char	*cwd = getcwd(NULL, 0);
	struct stat statbuf;

	head = args;
    args->next = NULL;
	for (int i = 0; argv[i] != NULL; ++i){ 
		args->name = ft_strdup(argv[i]);
		ft_strlcpy(args->path, cwd, PATH_MAX);
        ft_strlcat(args->path, "/", PATH_MAX);
        ft_strlcat(args->path, args->name, PATH_MAX);
		lstat(args->path, &statbuf);
        args->stats = statbuf;
        args->subdir = NULL;
		if (!argv[i+1]){
			args->next = NULL;
			break;	
		}
		args->next = malloc(sizeof(t_file));
		args = args->next;
	}
    //if no arguments given, it's equivalent to "ls ."
    if (!argv[0]){
        //dprintf(2, "No default args, going with .\n");
        args = add_file(cwd, ".");
    }
	free(cwd);
    return head;
}

int main(int argc, char** argv){
	int flags = 0;
    t_file *filelst;
    char **newargs;

	for (int i = 0; i < argc; ++i){
		set_flags(argv[i], &flags);
	}
    newargs = clean_args(argv, argc);
    if (!newargs){
        ft_dprintf(2, "Malloc error, exiting");
        return -1;
    }
	filelst = generate_list(newargs);
    free_array(newargs);
    if (flags & F_RECURS)
        find_subdirs(filelst);
    list_all(filelst, flags);
    //free_list(filelst);
}
