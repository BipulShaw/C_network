#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    struct hostent *host_entry;
    char host_name[1000];

    printf("Input Hostname: ");
    scanf("%s", host_name);

    host_entry = gethostbyname(host_name);
    if (host_entry == NULL){
        herror("gethostbyname");
        exit(1);
    }

    char ip = inet_ntoa((struct in_addr *)host_entry->h_addr);

    // printf("\nHostname: %s\n", hostbuffer);
    printf("\nHost IP: %s\n\n", ip);
    printf("Host Name: %s\n\n", host_entry->h_name);
    printf("Host Address Type: %d\n\n", host_entry->h_addrtype);
    printf("Address Length: %d\n\n", host_entry->h_length);

    printf("Address List: \n");
    struct in_addr *addr_list = (struct in_addr *)host_entry->h_addr_list;
    for (int i = 0; addr_list[i] != NULL; i++){
        printf("%d. %s\n", i + 1, inet_ntoa(*addr_list[i]));
    }
    printf("\n");

    printf("Aliases: \n");
    char **aliases = host_entry->h_aliases;
    for (int i = 0; aliases[i] != NULL; i++) {
        printf("%d. %s\n", i + 1, aliases[i]);
    }
    printf("\n");

    return 0;
}
