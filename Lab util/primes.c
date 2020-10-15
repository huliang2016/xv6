#include "kernel/types.h"
#include "user/user.h"

void filter(int *p)
{
    int n, temp, next_p[2];
    pipe(next_p);

    if (read(p[0], &n, sizeof(int)))
    {
        printf("prime %d\n", n);
        close(p[1]);
        if (fork() == 0)
        {
            // 子进程
            filter(next_p);
            exit(0);
        }
        else
        {
            // 父进程
            close(next_p[0]);
            while (read(p[0], &temp, sizeof(int)))
            {
                if (temp % n != 0)
                {
                    write(next_p[1], &temp, sizeof(int));
                }
            }
            close(next_p[1]);
            wait(0);
        }
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        fprintf(2, "Usage: primes\n");
        exit(1);
    }

    int p[2];
    pipe(p);

    if (fork() == 0)
    {
        // 子进程
        filter(p);
        exit(0);
    }
    else
    {
        // 父进程
        for (int i = 2; i <= 35; ++i)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    }

    exit(0);
}