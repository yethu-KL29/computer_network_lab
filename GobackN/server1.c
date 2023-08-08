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

    int seq_no;
    int frame_kind;
    int ack;
    Packet packet;
    int window_size;

} Frame;

int main()
{
    struct sockaddr_in client;

    int frame_id = 0;
    int ack_recv = 1;
    Frame fs, fr;

    socklen_t len = sizeof(client);

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

    bind(s, (struct sockaddr *)&client, sizeof(client));

    while (1)
    {

        int re = recvfrom(s, &fr, sizeof(fr), 0, (struct sockaddr *)&client, &len);
        if (re == -1)
        {
            perror("recvfrom");
            exit(1);
        }
        printf("Recieved Data: %s\n", fr.packet.data);
        printf("Acknoledgement for: %d send\n", fr.seq_no);

        fs.ack = 1;
        fs.seq_no = fr.seq_no;
        fs.frame_kind = 1;
        fs.window_size = 1;

        int se = sendto(s, &fs, sizeof(fs), 0, (struct sockaddr *)&client, sizeof(client));
    }
}
