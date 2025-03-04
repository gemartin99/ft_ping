#include "ft_ping.h"
#include <errno.h>
#include <netinet/ip_icmp.h>

//CHATGPT , HACER UNA PROPIA CUANDO LO ENTIENDA.
uint16_t checksum(void *b, int len) {
    uint16_t *buf = b;
    uint32_t sum = 0;
    while (len > 1) { sum += *buf++; len -= 2; }
    if (len == 1) sum += *(uint8_t*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    return ~sum;
}

void send_socket(t_ping *data)
{   
    int seq = 1;
    struct timeval start, end;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0)
    {
        fprintf(stderr, "Failed to create RAW socket\n");
        ft_exit(data);
    }
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    inet_pton(AF_INET, data->ip, &dest.sin_addr);

    struct icmp_hdr packet;
    memset(&packet, 0, sizeof(packet));
    packet.type = ICMP_ECHO;
    packet.id = getpid();

    char dest_ip_str[INET_ADDRSTRLEN];  // Para almacenar la IP en formato string
    inet_ntop(AF_INET, &dest.sin_addr, dest_ip_str, sizeof(dest_ip_str));
    printf("Sending packet to: %s\n", dest_ip_str);

    while (check_sigint == 0)
    {
        packet.seq = seq++;
        packet.checksum = 0;
        packet.checksum = checksum(&packet, sizeof(packet));

        printf("Sending packet:\n");
        printf("Type: %d\n", packet.type);
        printf("Code: %d\n", packet.code);
        printf("ID: %d\n", packet.id);
        printf("Seq: %d\n", packet.seq);
        printf("Checksum: %d\n", packet.checksum);

        gettimeofday(&start, NULL);
        sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&dest, sizeof(dest));
        if (recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL) > 0)
        {
            gettimeofday(&end, NULL);
            data->packets_received++;
            double rtt = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            printf("Reply from %s: seq=%d time=%.3f ms\n", data->ip, packet.seq, rtt);
        } 
        else
        {
            perror("recvfrom failed");
            printf("Error: %s\n", strerror(errno));
            printf("Request timed out\n");
        }
        sleep(1);
    }
}