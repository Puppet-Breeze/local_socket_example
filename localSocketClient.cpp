#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define LOCAL_DOMAIN "/tmp/local.domain"

int main(int argc, char** argv)
{
    int connect_fd;
    int ret;
    static struct sockaddr_un srv_addr;
    char send_buf[1024];

    /* creeate local socket */
    connect_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(connect_fd < 0) {
        perror("can not create local client socket\n");
        return -1;
    }

    /* connect server */
    srv_addr.sun_family = AF_UNIX;
    strncpy(srv_addr.sun_path, LOCAL_DOMAIN, sizeof(srv_addr.sun_path) - 1);
    ret = connect(connect_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if(ret == -1) {
        perror("can not connect to the server\n");
        close(connect_fd);
        return -1;
    }

    memset(send_buf, 0, sizeof(send_buf));
    strcpy(send_buf, "Holy Shit!");

    printf("ready to send...\n");
    int count = 1;
    while(true) {
        write(connect_fd, send_buf, sizeof(send_buf));
        sleep(3);
    }

    close(connect_fd);

    return 0;
}