#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *file_name)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot find path %s\n", path);
        exit(1);
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        exit(1);
    }

    if (st.type != T_DIR)
    {
        fprintf(2, "find: %s is not a directory\n", path);
        close(fd);
        exit(1);
    }

    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
    {
        fprintf(2, "find: path too long\n");
        close(fd);
        exit(1);
    }

    strcpy(buf, path);
    // 处理输入目录结尾为 / 的情况
    p = buf + strlen(buf) - 1;
    if (*p++ != '/')
    {
        *p++ = '/';
    }

    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        // 跳过 软链 . 和 ..
        if (de.inum == 0 || !strcmp(de.name, ".") || !strcmp(de.name, ".."))
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0)
        {
            fprintf(1, "find: cannot stat %s\n", buf);
            continue;
        }
        if (st.type == T_FILE && !strcmp(de.name, file_name))
        {
            fprintf(1, "%s\n", buf);
        }
        else if (st.type == T_DIR)
        {
            find(buf, file_name);
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        fprintf(2, "Usage: find (path) [file_name]\n");
        exit(1);
    }
    else if (argc < 3)
    {
        find(".", argv[1]);
    }
    else
    {
        find(argv[1], argv[2]);
    }

    exit(0);
}