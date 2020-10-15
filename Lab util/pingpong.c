#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        fprintf(2, "usage: pingpong\n");
        exit(1);
    }

    int p[2];
    pipe(p);
    char *buf = "";

    if (fork() == 0)
    {
        // 子进程
        // 读
        read(p[0], buf, 5);
        fprintf(1, "%d: received %s", getpid(), buf);
        close(p[0]);

        // 写
        write(p[1], "pong\n", 5);
        close(p[1]);
        exit(0);
    }
    else
    {
        // 父进程
        // 写
        write(p[1], "ping\n", 5);
        close(p[1]);

        // 等待子进程执行结束
        wait(0);
        
        // 读
        read(p[0], buf, 5);
        fprintf(1, "%d: received %s", getpid(), buf);
    }

    exit(0);
}
