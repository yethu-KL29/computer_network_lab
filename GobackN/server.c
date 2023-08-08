#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct packet
{

    char data[100];
} packet;
typedef struct frame
{
    int ack;
    int frame_kind;
    int sq_no;
    int window_size;
    packet packet;
} Frame;

int main()
{

    Frame fs, fr;
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    int s = socket(AF_INET, SOCK_DGRAM, 0);
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
    int ack_rec = 1;
    int frame_id = 0;
    while (1)
    {
        
        int r = recvfrom(s, &fr, sizeof(fr), 0, (struct sockaddr *)&server, &len); 
        if (r == -1)
        {
            perror("recv");
            exit(1);
        }

        printf("Message from server: %s\n", fr.packet.data);

        if (r > 0)
        {

            fs.ack = 1;
            fs.frame_kind = 1;
            fs.sq_no = fr.sq_no;
            fs.window_size = 1;

            int se = sendto(s, &fs, sizeof(fs), 0, (struct sockaddr *)&server, len);
            if (se == -1)
            {
                perror("send");
                exit(1);
            }
            printf("Ack sent\n");
        }
    }
}