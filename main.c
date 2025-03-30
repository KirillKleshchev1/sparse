#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUF_SIZE 4096


int main(int argc, char** argv) {
    int bufS = BUF_SIZE;
    int opt;
    while (opt = getopt(argc, argv, "b:") != -1) {
        if (opt == 'b') {
            bufS = atoi(optarg);
        }

    }

    int index = optind;

    int fd_in = STDIN_FILENO;


    if (argv[optind+1] != NULL) {
        index++;
        fd_in = open(argv[optind], O_RDONLY);
    }

    int fd_out = open(argv[index], O_TRUNC | O_WRONLY | O_CREAT, 0777);


    char buf[bufS];
    ssize_t bytes_read;

    while ((bytes_read = read(fd_in, buf, bufS)) > 0) {
        char *p = buf;
        while (p < buf + bytes_read && *p == 0)
            p++;

        if (p == buf + bytes_read)
            lseek(fd_out, bytes_read, SEEK_CUR);
        else
            write(fd_out, buf, bytes_read);
    }

    if (fd_in != STDIN_FILENO)
        close(fd_in);
    close(fd_out);

    return 0;
}
