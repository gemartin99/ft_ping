#include "ft_ping.h"

void ft_exit(t_ping *data)
{
    if (data)
        free(data);
    exit(1);
}

void ft_exit_error(t_ping *data, char *msg)
{
    if (data)
        free(data);
    if (msg)
        fprintf(stderr, "%s\n", msg);
    exit(1);
}

void print_help(t_ping *data)
{
    printf("Usage: ft_ping [options] <host>\n");
    printf("  -h         Show help\n");
    printf("  -s         No show reply outputs, only final stats\n");
    printf("  -ttl <num> Set TTL value for the packets\n");
    printf("  -i <num>   Set the interval (in seconds) between each ping request\n");
    printf("  -l <num>   Number of packets to send before receiving a reply\n");
    printf("  -t         Show local time when receiving packets\n");

    if (data)
        free(data);

    exit(0);
}


void handle_sigint(int sig)
{
    (void)sig;
    double packet_loss = ((double)(packets_sent - packets_received) / packets_sent) * 100;
    printf("\n--- Ping statistics ---\n");
    printf("%d packets transmitted, %d received, %.1f%% packet loss\n", packets_sent, packets_received, packet_loss);
    close(sock);
    exit(1);
}
