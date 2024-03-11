#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FILEPATH "/home/john/repos/kernel-crafter/memory-mapping/sample1.txt"
#define BUFFER_SIZE 10024

int main() {
    int fd = open (FILEPATH, O_RDONLY);

    if (fd == -1) {
        perror ("open");
        return 1;
    }

    int res;

   struct stat statbuf;

    res = fstat(fd, &statbuf);

    if (res == -1) {
        perror ("fstat");
        return 1;
    }

    void* p = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED_VALIDATE, fd, 0);

    if (p == MAP_FAILED){
        perror ("mmap");
        return 1;
    }

    char buffer[BUFFER_SIZE-1];

    strncpy(buffer, p, BUFFER_SIZE-1);
    buffer[BUFFER_SIZE] = '\0';

    printf("%s\n", buffer);
    return 0;
}
