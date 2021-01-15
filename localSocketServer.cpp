#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define LOCAL_DOMAIN "/tmp/local.domain"

int main(int argc, char** argv)
{
    int server_fd;
    int connect_fd;
    int ret;
    socklen_t clt_addr_len;
    struct sockaddr_un srv_addr;
    struct sockaddr_un clt_addr;
    char recv_buf[1024];

    /* creeate local socket */
    server_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(server_fd < 0) {
        perror("can not create local server socket\n");
        return -1;
    }

    /* bind socket to local address */
    srv_addr.sun_family = AF_UNIX;
    strncpy(srv_addr.sun_path, LOCAL_DOMAIN, sizeof(srv_addr.sun_path) - 1);
    unlink(LOCAL_DOMAIN);
    ret = bind(server_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if(ret == -1) {
        perror("can not bind local server socket\n");
        close(server_fd);
        unlink(LOCAL_DOMAIN);
        return -1;
    }

    /* listen client socket connect */
    ret = listen(server_fd, 1);
    if(ret == -1) {
        perror("can not listen the client socket connect request\n");
        close(server_fd);
        unlink(LOCAL_DOMAIN);
        return -1;
    }

    /* accept client socket connect */
    clt_addr_len = sizeof(clt_addr);
    connect_fd = accept(server_fd, (struct sockaddr*)&clt_addr, &clt_addr_len);
    if(connect_fd < 0) {
        perror("can not accept client socket connect request");
        close(server_fd);
        unlink(LOCAL_DOMAIN);
        return -1;
    }

    printf("ready ro receive...\n");
    while(true) {
        memset(recv_buf, 0, sizeof(recv_buf));
        int count = read(connect_fd, recv_buf, sizeof(recv_buf));
        if (count > 0) {
            printf("receive %d bytes message from client: %s\n", count, recv_buf);
        }
    }

    close(connect_fd);
    close(server_fd);
    unlink(LOCAL_DOMAIN);

    return 0;
}