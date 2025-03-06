#include "ft_ping.h"
#include <errno.h>
#include <netinet/ip_icmp.h>


uint16_t checksum(void *b, int len) {
    uint16_t *buf = b;
    uint32_t sum = 0;
    while (len > 1) { sum += *buf++; len -= 2; }
    if (len == 1) sum += *(uint8_t*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    return ~sum;
}

void print_ttl_reply(char *buffer) {
    struct ip *ip_header = (struct ip *)buffer;  // El header IP esta al principio del buffer
    int ttl = ip_header->ip_ttl;  // TTL esta en el campo ip_ttl del header IP
    printf(" ttl=%d", ttl);
}

void send_socket(t_ping *data)
{   
    int reply_bytes = 0;
    int seq = 1;
    struct timeval start, end;
    char buffer[1024];
    time_t now;
    struct tm *local_time;

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0)
    {
        fprintf(stderr, "Failed to create RAW socket\n");
        ft_exit(data);
    }

    if (setsockopt(sock, IPPROTO_IP, IP_TTL, &data->ttl, sizeof(data->ttl)) != 0)
    {
        fprintf(stderr, "Failed to set TTL\n");
        ft_exit(data);
    }

    struct sockaddr_in dest; //strcut para guardar ip en formato bin
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    inet_pton(AF_INET, data->ip, &dest.sin_addr);

    struct icmp_hdr packet; //struct informacion packete
    memset(&packet, 0, sizeof(packet));
    packet.type = ICMP_ECHO;
    packet.id = getpid();

    char dest_ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &dest.sin_addr, dest_ip_str, sizeof(dest_ip_str));
    printf("PING %s (%s)\n", dest_ip_str, dest_ip_str);
    while (check_sigint == 0)
    {
        if (data->num_packets != -1 && packet.seq >= data->num_packets)
            break;
        packet.seq = seq++;
        packet.checksum = 0;
        packet.checksum = checksum(&packet, sizeof(packet));

        gettimeofday(&start, NULL);
        sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&dest, sizeof(dest));
        packets_sent = packet.seq;
        reply_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
        if (reply_bytes > 0)
        {
            if (data->time == true)
            {
                time(&now);
                local_time = localtime(&now);
                printf("[%02d:%02d:%02d] ", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
            }
            gettimeofday(&end, NULL);
            packets_received++;
            double rtt = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            if (data->silent == false)
            {
                printf("%d bytes from %s: icmp_seq=%d", reply_bytes, data->ip, packet.seq);
                print_ttl_reply(buffer);
                printf(" time=%.3f ms\n", rtt);
            }
        } 
        else
        {
            fprintf(stderr, "Request timed out\n");
        }
        if (data->num_packets != -1 && packet.seq >= data->num_packets)
            break;
        sleep(data->interval);
    }
    double packet_loss = ((double)(packets_sent - packets_received) / packets_sent) * 100;
    printf("\n--- Ping statistics ---\n");
    printf("%d packets transmitted, %d received, %.1f%% packet loss\n", packets_sent, packets_received, packet_loss);
    close(sock);
    free(data);
}
