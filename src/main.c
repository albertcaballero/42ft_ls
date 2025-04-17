#include "../ft_ls.h"

// -l, long format F_LONG
// -R, --recursive, recursive  F_RECURS
// -a, --all, show files starting with . (hidden) F_ALL
// -r, --reverse, reverse order F_REVERSE
// -t, sort by time, newest first F_TIME


void print_list(t_file *lst);

void set_flags(char* arg, int *flags){
	if (!arg || ft_strlen(arg) == 0){
		return;
	}
	if (arg[0] != '-'){
		return;
	}
	//add --help functionality maybe??
	for (int i = 1; arg[i] != 0; ++i){
		switch (arg[i]){
			case 'l':
				*flags |= F_LONG;
				break;
			case 'R':
				*flags |= F_RECURS;
				break;
			case 'a':
				*flags |= F_ALL;
				break;
			case 'r':
				*flags |= F_REVERSE;
				break;
			case 't':
				*flags |= F_TIME;
				break;
			default:
				ft_dprintf(2, "ft_ls: invalid option -- '%c'\n", arg[i]);
				exit(2);
				break;
		}
	}
}

void generate_list(int argc, char **argv){
	t_file *head=NULL;
	t_file* args=malloc(sizeof(t_file));
	char	*pwd = getcwd(NULL, 0);
	head = args;
	for (int i = 1; i < argc; ++i){ 
		if (argv[i][0] == '-'){
			continue;
		}
		args->name = ft_strdup(argv[i]);
		args->path = ft_strjoin(cwd, argv[i]);
		args->type = FIL; //check with stat/lstat
		if (i+1 == argc){
			args->next = NULL;
			break;	
		}
		args->next = malloc(sizeof(t_file));
		args = args->next;
	}
	print_list(head);
	free(pwd);
}

void print_list(t_file *lst){
	for (;lst!=NULL;lst=lst->next){
		ft_dprintf(1, "LST: %s, %d, %s\n",lst->name, lst->type, lst->subdir);
	}
}

int main(int argc, char** argv){
	int flags = 0;

	for (int i = 0; i < argc; ++i){
		set_flags(argv[i], &flags);
	}
	generate_list(argc, argv);
}
