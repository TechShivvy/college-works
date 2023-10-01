#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <fcntl.h>

int main()
{
    int top=0,stack[100];

    int fd = open("quick_sort.py", O_RDONLY);
    char buffer[1024];
    ssize_t n;

    while ((n = read(fd, buffer, 1)) > 0) {
        if(buffer[i]=='\n')
        {
            printf("NEWLINE\n");
            n=read(fd,buffer,1)
            if(buffer[0]=='\t')
        }
    }

    close(fd);
    return 0;
}