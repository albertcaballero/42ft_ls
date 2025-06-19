#ifndef FT_LS_H_
#define FT_LS_H_

#include "libft/libft.h"
#include <limits.h>
#include <sys/stat.h>

//Define flags
#define F_LONG		(1 << 0)
#define F_RECURS	(1 << 1)
#define F_ALL		(1 << 2)
#define F_REVERSE	(1 << 3)
#define F_TIME		(1 << 4)

/* Set a flag	user_flags	|= FLAG;
Clear a flag	user_flags &= ~FLAG;
Toggle a flag	user_flags ^= FLAG;
Check a flag	if (user_flags & FLAG)
*/

enum Type {
	FIL,
	DIR,
	SYML,
	BLOCK,
	DEV,
	PIPE,
	SOCK
};

typedef struct s_file
{
	char 	*name;
	char	path[PATH_MAX];
    struct stat stats;
	struct s_file	*next;
	struct s_file	*subdir;
	enum Type	type;
} t_file;

//parsing
void set_flags(char* arg, int *flags);
char **clean_args(char **argv, int argc);

//printing
void list_all(t_file *list, int flags);

//HELPERS
void print_stats(struct stat buf);
void print_list(t_file *lst);
size_t file_list_size(t_file *lst);

//sorting

//t_file list creation
void find_subdirs(t_file *lst);
t_file *add_file(char *path, char *name);

#endif
