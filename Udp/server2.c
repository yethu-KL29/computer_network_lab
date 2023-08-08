#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){


   
      

      int n;

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

        int r = recvfrom(s,&n,sizeof(n),0,(struct sockaddr*)&server,&len);

        int flag = 0;
        char buffer[100];

        if(r>0){
            printf("Number received from client: %d\n",n);

            for(int i = 2;i<=n/2 ;i++){

                if(n%i == 0){
                   flag = 1;
                   break;
                }

            }

            if(flag == 0){
               strcpy(buffer,"Number is prime");
            }
            else{
               strcpy(buffer,"Number is not prime");
            }

            sendto(s,buffer,100,0,(struct sockaddr*)&server,sizeof(server));
        }
        else{
            printf("Error receiving number from client\n");
        }

}