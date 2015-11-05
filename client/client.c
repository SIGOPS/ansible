#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int s;
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM; /* TCP */

    s = getaddrinfo("remlnx.ews.illinois.edu", "65123", &hints, &result);
    if (s != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            exit(1);
    }

    connect(sock_fd, result->ai_addr, result->ai_addrlen);

    char* line=NULL;
    FILE* fp=stdin;
    size_t len=0;
    
    while(getline(&line,&len,fp)!=-1){
        printf("SENDING: %s", line);
        printf("===\n");
        write(sock_fd, buffer, strlen(buffer));
        
    }
    
    char resp[1000];
    int len = read(sock_fd, resp, 999);
    resp[len] = '\0';
    printf("%s\n", resp);

    return 0;
}
