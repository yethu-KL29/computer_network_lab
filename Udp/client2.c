#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
     

     struct sockaddr_in client;
     socklen_t len = sizeof(client);

        int s = socket(AF_INET,SOCK_DGRAM,0);   
        if(s == -1){
            perror("socket");
            exit(1);
        }
        bzero(&client,sizeof(client));

        client.sin_family = AF_INET;
        client.sin_addr.s_addr = INADDR_ANY;
        client.sin_port = htons(6000);

        printf("Enter number: ");
        int n;
        scanf("%d",&n);


        sendto(s,&n,sizeof(n),0,(struct sockaddr*)&client,sizeof(client));

        char buffer[100];
        recvfrom(s,buffer,100,0,(struct sockaddr*)&client,&len);
        

        printf("Message from server: %s\n",buffer);


}