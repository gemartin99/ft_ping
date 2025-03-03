#include "ft_ping.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

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