#include "ft_ls.h"

// -l, long format F_LONG
// -R, --recursive, recursive  F_RECURS
// -a, --all, show files starting with . (hidden) F_ALL
// -r, --reverse, reverse order F_REVERSE
// -t, sort by time, newest first F_TIME

void parse_arg(char* arg, int flags){
	if (!arg || ft_strlen(arg) == 0){
		return;
	}
	if (arg[0] != '-'){
		return;
	}
	for (int i = 0; arg[i] != 0; ++i){
		switch (arg[i]){
			case 'l':
				flags |= F_LONG;
				break;
			case 'R':
				flags |= F_RECURS;
				break;
			case 'a':
				flags |= F_ALL;
				break;
			case 'r':
				flags |= F_REVERSE;
				break;
			case 't':
				flags |= F_TIME;
				break;
			default:
				ft_dprintf(2, "ls: invalid option -- '%c'\n", arg[i]);
				exit(2);
				break;
		}
	}
}

int main(int argc, char** argv){
	int flags = 0;
	for (int i = 0; i < argc; ++i){
		parse_arg(argv[i], flags);
	}
}
