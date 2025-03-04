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
    printf("  -v         Verbose mode\n");
    printf("  -h         Show help\n");
    printf("  -f         Flood ping (send packets as fast as possible)\n");
    printf("  -n         Do not resolve hostnames, show only IP addresses\n");
    printf("  -l <num>   Number of packets to send before receiving a reply\n");
    printf("  -r         Bypass routing table, send directly to the interface\n");

    if (data)
        free(data);

    exit(0);
}

void handle_sigint(int sig)
{
    (void)sig;
    printf("\n--- Ping statistics ---\n");
    /*printf("%d packets transmitted, %d received, %.1f%% packet loss\n",
           data->packets_sent, data->packets_received,
           ((data->packets_sent - data->packets_received) / (double)data->packets_sent) * 100);
    */close(sock);
    //free(data);
    exit(0);
}
