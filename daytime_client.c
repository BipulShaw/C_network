#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc)
{
    int sockfd;

    // creating the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Problem in creating the socket");
        exit(2);
    }

    printf("Socket Created successfully!!\n");

    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(8080);          

    // connecting to the server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Problem in connecting to the server");
        exit(3);
    }

    printf("Connected to the server!\n");

    char str[100];

    if (read(sockfd, str, sizeof(str)) == 0)
    {
        perror("The server terminated prematurely");
        exit(1);
    }

    printf("%s", "Data received from the server: ");
    fputs(str, stdout);

    return 0;
}
