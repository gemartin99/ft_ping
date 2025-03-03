#ifndef FT_PING_H
#define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <sys/socket.h>


typedef struct s_ping
{
    char *ip;
    bool verbose; //-v
    bool flood; //-f
    int preload; //-l <num> numero de paketes a enviar antes de recibir respuesta
    bool numeric; // -n
    bool ip_timestamp; // --ip-timestamp
    bool bypass_routing; //-r
    bool help; //-h

} t_ping;

void    ft_exit(t_ping *data);
void    ft_exit_error(t_ping *data, char *msg);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void    print_help(t_ping *data);

#endif