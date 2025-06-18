
#include "../ft_ls.h"


// -l, long format F_LONG
// -R, --recursive, recursive  F_RECURS
// -a, --all, show files starting with . (hidden) F_ALL
// -r, --reverse, reverse order F_REVERSE
// -t, sort by time, newest first F_TIME


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

char **clean_args(char **argv, int argc){
    int count = 0;
    char **newargs;
    for (int i = 1; i < argc; ++i){
       if (argv[i][0] != '-')
           ++count;
    }
    newargs = malloc((count+1) * sizeof(char *));
    if (!newargs)
        return NULL;

    count = 0;
    for (int i = 1; i < argc; ++i){
       if (argv[i][0] != '-'){
           newargs[count] = ft_strdup(argv[i]);
           ++count;
       }
    }
    newargs[count] = NULL;
    return newargs;
}
