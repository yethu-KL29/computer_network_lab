#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){


    struct sockaddr_in client;

    int s = socket(AF_INET,SOCK_DGRAM,0);

    if(s == -1){
        perror("socket");
        exit(1);
    }

    bzero(&client,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(6000);

    socklen_t len = sizeof(client);

    while(1){
        printf("enter the file name");
        char buffer[100];
        scanf("%s",buffer);

        sendto(s,buffer,100,0,(struct sockaddr*)&client,sizeof(client));


        char buffer1[100];
        recvfrom(s,buffer1,100,0,(struct sockaddr*)&client,&len);

        for(int i=0;i<strlen(buffer1);i++){
            if(buffer1[i] == EOF){
                break;
            }
            printf("%c",buffer1[i]);
        }


    }



}