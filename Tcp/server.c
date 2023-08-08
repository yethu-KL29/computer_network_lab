#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main()
{
 char buffer[100];
    struct sockaddr_in server;
    socklen_t len  = sizeof(server);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        perror("socket");
        exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(6000);

    bind(s, (struct sockaddr *)&server, sizeof(server));
    listen(s, 6);
    int a = accept(s, (struct sockaddr *)&server, &len);

    recv(a,buffer,100,0);

    printf("Message from client: %s\n", buffer);

   
}