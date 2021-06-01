#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("%s\n","Please input your target IP address.");
        return 1;
    }
    struct sockaddr_in sa;
    int sockfd = 0;
    char sendstr[100];
    char recvstr[100];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset((void*)&sa, 0, sizeof (sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons((uint16_t) 80);
    inet_pton(AF_INET, argv[1], &sa.sin_addr);
    if (connect(sockfd, (struct sockaddr *) &sa, sizeof(sa))<0) {
        perror("Error: Failed to establish connection with target IP.");
    }
    sprintf(sendstr, "GET / HTTP/1.1\r\n\r\n");

    write(sockfd, sendstr, strlen(sendstr));
    ssize_t n;
    while ((n=read(sockfd, recvstr, 99)) > 0) {
        printf("%s",recvstr);
        memset(recvstr, 0, 100);
        if (n < 0) {
            perror("Error:");
            return 0;
        }   
    }
    close(sockfd);
    exit(0);
    return 0;
}