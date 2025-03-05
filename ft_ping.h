#ifndef FT_PING_H
#define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/time.h>
#include <netinet/ip_icmp.h>

extern int sock;
extern int check_sigint;
extern int packets_sent;
extern int packets_received;

// Definimos nuestra propia estructura ICMP
struct icmp_hdr {
    uint8_t type;        // Tipo de mensaje ICMP
    uint8_t code;        // Código del mensaje
    uint16_t checksum;   // Checksum
    uint16_t id;         // Identificador
    uint16_t seq;        // Número de secuencia
};

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
void    print_help(t_ping *data);
void    handle_sigint(int sig);

void    send_socket(t_ping *data);

#endif