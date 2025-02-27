/*typedef struct s_ping
{
    char *ip;
    bool verbose; //-v
    bool flood; //-f
    int preload; //-l <num> numero de paketes a enviar antes de recibir respuesta
    bool numeric; // -n
    bool ip_timestamp; // --ip-timestamp
    bool bypass_routing; //-r
    bool help; //-h

} t_ping
*/

#include "ft_ping.h"

void parse(int argc, char **argv, t_ping *data)
{
    if (argc == 2 && !strcmp(argv[1], "-?"))
        print_help(data);

    
}


t_ping *init_struct()
{
    t_ping *data = (t_ping *)malloc(sizeof(t_ping));
    if (!data)
        ft_exit(NULL);
    ft_bzero(data, sizeof(*data));
    data->ip = NULL;
}

int main(int argc, char **argv)
{
    t_ping *data = init_struct();
    parse(argc, argv);
}