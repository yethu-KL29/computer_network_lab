#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){


    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    int s = socket(AF_INET,SOCK_DGRAM,0);

    if(s == -1){
        perror("socket");
        exit(1);
    }

    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(6000);

    bind(s,(struct sockaddr*)&server,sizeof(server));
    FILE *fp;

    while(1){
       
        char buffer1[100];
        recvfrom(s,buffer1,100,0,(struct sockaddr*)&server,&len); 
        fp = fopen(buffer1,"r"); 

        if(fp == NULL){
            printf("file not found");
            exit(1);
        }

        char buffer[100];
        for(int i=0;i<100;i++){
            
            buffer[i] = fgetc(fp)^'S';
           
        }

        sendto(s,buffer,100,0,(struct sockaddr*)&server,sizeof(server));

        


    }



}