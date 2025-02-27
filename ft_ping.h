#ifndef FT_PING_H
#define FT_PING_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
    char *ip;
    bool verbose; //-v
    bool flood; //-f
    int preload; //-l <num> numero de paketes a enviar antes de recibir respuesta
    bool numeric; // -n
    bool ip_timestamp; // --ip-timestamp
    bool bypass_routing; //-r
    bool help; //-h

} t_data;

void ft_exit(t_ping *data);

#endif