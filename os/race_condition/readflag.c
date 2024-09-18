#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd = 0;
    int size = 0;
    char buf[256];

    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    struct stat stat_data;
    if (stat(argv[1], &stat_data) < 0)
    {
        fprintf(stderr, "Failed to stat %s: %s\n", strerror(errno));
        exit(1);
    }

    if (stat_data.st_uid == 0)
    {
        fprintf(stderr, "File %s owned by root\n", argv[1]);
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);

    if (fd <= 0)
    {
        fprintf(stderr, "Couldn't open the file %s\n", argv[1]);
        exit(1);
    }

    do
    {
        size = read(fd, buf, 256);
        write(1, buf, size);
    } while (size > 0);
}