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

    char *ip;
    bool verbose; //-v
    bool flood; //-f
    int preload; //-l <num> numero de paketes a enviar antes de recibir respuesta
    bool numeric; // -n
    bool ip_timestamp; // --ip-timestamp
    bool bypass_routing; //-r
    bool help; //-h

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