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

    int s = socket(AF_INET,SOCK_STREAM,0);

    if(s == -1){
        perror("socket");
        exit(1);
    }

    bzero(&client,sizeof(client));

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(6000);


   bind(s,(struct sockaddr*)&client,sizeof(client));
   listen(s,5);
   int a = accept(s,(struct sockaddr*)&client,&len);

  char buffer[100];

  recv(a,buffer,100,0);

  char rev[100];

    printf("Message from client: %s\n",buffer);

    int j=0;

    for(int i=strlen(buffer)-1;i>=0;i--){

        rev[j]= buffer[i];
        j++;

        

        
    }
    rev[j]='\0';

    printf("Reversed string: %s\n",rev);


   

    

  


    


}