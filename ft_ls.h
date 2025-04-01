#ifndef FT_LS_H_
#define FT_LS_H_

#include "libft/libft.h"

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

typedef struct file
{
	char 	*name;
	struct file	*next;
	struct file	*subdir;
	int		type;
} t_file;



#endif