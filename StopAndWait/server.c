#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct packet
{
    char data[100];
} Packet;

typedef struct frame
{
    int ack;
    int frame_kind;
    int sq_no;
    Packet packet;

} Frame;

int main()
{

    struct sockaddr_in server,client;
    Frame fs, fr;

    int ack_rec = 1;
    int Frame_id = 0;

    int s = socket(AF_INET,SOCK_DGRAM, 0);
    if (s == -1)
    {
        perror("socket");
        exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(6000);

    int b = bind(s, (struct sockaddr *)&server, sizeof(server));

    socklen_t len = sizeof(client);

    while (1)
    {

        int r = recvfrom(s, &fr, sizeof(fr), 0, (struct sockaddr *)&client, &len);
        if (r == -1)
        {
            perror("recv");
            exit(1);
        }
        if(r>0){
            printf("Message from server: %s\n", fr.packet.data);

            fs.ack =1;
            fs.frame_kind = 1;
            fs.sq_no =fr.sq_no;

            int se = sendto(s, &fs, sizeof(fs), 0, (struct sockaddr *)&client, sizeof(client));
            if (se == -1)
            {
                perror("send");
                exit(1);
            }
            printf("Ack sent\n");
        }

    }
}