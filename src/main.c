#include "../ft_ls.h"

t_file* generate_list(char **argv){
	t_file *head=NULL;
	t_file* args=malloc(sizeof(t_file));
	char	*cwd = getcwd(NULL, 0);

	head = args;
    args->next = NULL;
	for (int i = 0; argv[i] != NULL; ++i){
	    add_file(cwd, argv[i], args);
		if (!argv[i+1]){
			break;
		}
		args->next = malloc(sizeof(t_file));
		args = args->next;
	}
    //if no arguments given, it's equivalent to "ls ."
    if (!argv[0]){
        //dprintf(2, "No default args, going with .\n");
        add_file(cwd, ".", args);
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
