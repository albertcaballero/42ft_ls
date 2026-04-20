
#include "../ft_ls.h"

static int int_len(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void ft_padding_str(int max, int current, char *str)
{
    int spaces = max - current;
    while (spaces-- > 0)
        write(1, " ", 1);
    ft_dprintf(1, "%s ", str);
}

static void ft_padding_int(int max, int current, int num)
{
    int spaces = max - current;
    while (spaces-- > 0)
        write(1, " ", 1);
    ft_dprintf(1, "%i ", num);
}

static char get_file_type(int mode)
{
	mode = (mode & S_IFMT);
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

static char *display_file_perm(char *chmod, int mode)
{
	chmod[0] = get_file_type(mode);
	chmod[1] = (S_IRUSR & mode) ? 'r' : '-';
	chmod[2] = (S_IWUSR & mode) ? 'w' : '-';
	chmod[3] = (S_IXUSR & mode) ? 'x' : '-';
	chmod[4] = (S_IRGRP & mode) ? 'r' : '-';
	chmod[5] = (S_IWGRP & mode) ? 'w' : '-';
	chmod[6] = (S_IXGRP & mode) ? 'x' : '-';
	chmod[7] = (S_IROTH & mode) ? 'r' : '-';
	chmod[8] = (S_IWOTH & mode) ? 'w' : '-';
	chmod[9] = (S_IXOTH & mode) ? 'x' : '-';
	chmod[10] = '\0';
	if (S_ISUID & mode)
		chmod[3] = chmod[3] == '-' ? 'S' : 's';
	if (S_ISGID & mode)
		chmod[6] = chmod[6] == '-' ? 'S' : 's';
	if (S_ISVTX & mode)
		chmod[9] = chmod[9] == '-' ? 'T' : 't';
    return chmod;
}

t_colwidth get_col_widths(t_file *files)
{
    t_colwidth w = {0};
    t_file *current = files;

    while (current)
    {
        struct passwd *pw = getpwuid(current->stats.st_uid);
        struct group  *gr = getgrgid(current->stats.st_gid);

        int links = int_len((int)current->stats.st_nlink);
        int size  = int_len((int)current->stats.st_size);
        int user  = pw ? ft_strlen(pw->pw_name) : 7;
        int group = gr ? ft_strlen(gr->gr_name) : 7;

        if (links > w.links) w.links = links;
        if (size  > w.size)  w.size  = size;
        if (user  > w.user)  w.user  = user;
        if (group > w.group) w.group = group;

        current = current->next;
    }
    return w;
}

void print_symlink(t_file *file){
    if (!S_ISLNK(file->stats.st_mode))
        return;
    char buf[PATH_MAX];
    ssize_t len = readlink(file->path, buf, sizeof(buf) - 1);
    if (len != -1)
    {
        buf[len] = '\0';
        ft_dprintf(1, " -> %s", buf);
    }
}

void list_file_all(t_file *file, t_colwidth widths){
    char perms[11];

    //time
    char time_buf[13];
    struct tm *tm_info;
    tm_info = localtime(&file->stats.st_mtime);
    time_t now = time(NULL);
    if (now - file->stats.st_mtime > 15552000) // ~6 months
        strftime(time_buf, sizeof(time_buf), "%b %e  %Y", tm_info);
    else
        strftime(time_buf, sizeof(time_buf), "%b %e %H:%M", tm_info);

    //user and group
    struct passwd *pw = getpwuid(file->stats.st_uid);
    struct group  *gr = getgrgid(file->stats.st_gid);
    char *user  = pw ? pw->pw_name : "unknown";
    char *group = gr ? gr->gr_name : "unknown";

    // ft_dprintf(1, "%s %i %s %s %i %s %s\n",
    //         display_file_perm(perms, file->stats.st_mode),
    //         file->stats.st_nlink,
    //         user,group,
    //         file->stats.st_size,
    //         time_buf,
    //         file->name);

    ft_dprintf(1, "%s ", display_file_perm(perms, file->stats.st_mode));
    ft_padding_int(widths.links, int_len(file->stats.st_nlink), file->stats.st_nlink);
    ft_padding_str(widths.user, ft_strlen(user), user);
    ft_padding_str(widths.group, ft_strlen(group), group);
    ft_padding_int(widths.size, int_len(file->stats.st_size), file->stats.st_size);
    ft_dprintf(1, "%s %s", time_buf, file->name);
    print_symlink(file);
    ft_dprintf(1, "\n");
}
