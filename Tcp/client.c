#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){

   

    struct sockaddr_in client;

    int s = socket(AF_INET,SOCK_STREAM,0);
    if(s == -1){
        perror("socket");
        exit(1);
    }
    bzero(&client,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(6000);


    connect(s,(struct sockaddr*)&client,sizeof(client));

    printf("Connected to server\n");
    

    char buffer[100];
    printf("Enter message to send to server: ");
    scanf("%s",buffer);
    send(s,buffer,100,0);
    
}