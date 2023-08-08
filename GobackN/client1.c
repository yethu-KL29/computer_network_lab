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

    printf("Enter window size: ");
    scanf("%d", &fs.window_size);

    while (1)
    {

        if (ack_recv == 1)
        {

            fs.seq_no = frame_id;
            fs.ack = 0;
            fs.frame_kind = 0;

            for (int i = 0; i < fs.window_size; i++)
            {
                printf("Enter data for frame %d\n: ", frame_id);
                scanf("%s", fs.packet.data);
                int se = sendto(s, &fs, sizeof(fs), 0, (struct sockaddr *)&client, sizeof(client));
                if (se > 0)
                {
                    printf("Frame sent\n");
                }
                else
                {
                    printf("Frame not sent\n");
                }
            }
        }

        int re = recvfrom(s, &fr, sizeof(fr), 0, (struct sockaddr *)&client, &len);
        if (re > 0)
        {
            printf("Ack received for frame %d", fr.seq_no);
            ack_recv = 1;
            frame_id++;
            fs.window_size = fr.window_size;
        }
        else
        {
            printf("Ack not received\n");
        }
    }
}
