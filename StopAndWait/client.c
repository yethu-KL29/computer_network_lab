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

    struct sockaddr_in client;
    Frame fs, fr;

    int ack_rec = 1;
    int Frame_id = 0;

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1)
    {
        perror("socket");
        exit(1);
    }
    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(6000);
    socklen_t len = sizeof(client);

    while (1)
    {

        if (ack_rec == 1)
        {

            fs.frame_kind = 0;
            fs.sq_no = Frame_id;
            fs.ack = 0;

            printf("Enter message to send to server: ");
            scanf("%s", fs.packet.data);

            int se = sendto(s, &fs, sizeof(fs), 0, (struct sockaddr *)&client, sizeof(client));
            if (se == -1)
            {
                perror("send");
                exit(1);
            }
            printf("Frame %d sent\n", fs.sq_no);
            ack_rec = 0;
        }

        int re = recvfrom(s, &fr, sizeof(fr), 0, (struct sockaddr *)&client, &len);
        if (re == -1)
        {
            perror("recv");
            exit(1);
        }
        ack_rec = 1;
        
        if (fr.ack == 1)
        {
            printf("ack %d recieved\n", fr.sq_no);
            Frame_id++;
        }

    }
}