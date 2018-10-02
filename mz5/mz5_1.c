#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int 
main(int argc, char const *argv[])
{
    int f = open(argv[1], O_RDWR);
    if (-1 == f){
        return 1;
    }
    long long int min, buf, n, t = 0;
    int flag = read(f, &min, 8);
    if (flag < 0){
        return 1;
    } 
    if (flag == 0){
        return 0;
    }
    n = 0;
    while (read(f, &buf, 8) > 0){
        t++;
        if (buf < min) {
            min = buf;
            n = t;
        }
    }
    min = -min;
    lseek(f, sizeof(min)*n, SEEK_SET);
    write(f, &min, 8);
    close(f);


    return 0;
}