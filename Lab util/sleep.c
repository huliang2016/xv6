#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "usage: sleep seconds\n");
        exit(1);
    }

    int seconds = atoi(argv[1]);
    if (seconds > 0)
    {
        fprintf(1, "sleep for %d seconds\n", seconds);
        // 在 user.h 中有声明，但是实现是其他语言实现的，参见 usys.S line 98
        sleep(seconds);
    }
    else
    {
        fprintf(2, "Invalid interval %s\n", argv[1]);
    }

    exit(0);
}
