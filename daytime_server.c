#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>

#define PORT 8080

char* getDayTime(){
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    printf ("Server daytime: %s\n", asctime(timeinfo));

    return asctime(timeinfo);
}

int main(){

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1){
        perror("socket");
        exit(1);
    }
    
    //assign ip, port
    struct sockaddr_in addr;
    // bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    
    //bind
    int bind_fd = bind(sock_fd, (struct sockaddr *) &addr, sizeof(addr));
    if(bind_fd == -1){
        perror("bind");
        exit(1);
    }

    int listen_fd = listen(sock_fd, 2);
    if(listen_fd == -1){
        perror("listen");
        exit(1);
    }
    else printf("Server Listening ...\n");

    struct sockaddr_in cli;
    int len = sizeof(cli);
    int conn_fd = accept(sock_fd, (struct sockaddr *) &cli, &len);
    if(conn_fd == -1){
        printf("Connection to client failed...\n");
        perror("listen");
        exit(1);
    }
    else printf("Connection from client accepted...\n");

    //Daytime Code
    char *buffer = getDayTime();
    
    write(conn_fd, buffer, 100);
    // write(conn_fd, buffer, sizeof(buffer));
    // read(conn_fd, buffer, sizeof(buffer));

    printf("Data sent to client...\n");
    //Daytime Code

    close(sock_fd);

    return 0;
}
