#include "ft_ping.h"

int sock;
int check_sigint;

int valid_ip(char *ip)
{
    struct sockaddr_in sa;

    if (inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1)
        return 1;
    return 0;
}

int valid_hostname(char *hostname)
{
    struct hostent *_host = gethostbyname(hostname);

    if (_host != NULL)
        return 0;
    return 1;
}

void parse(int argc, char **argv, t_ping *data)
{
    int i = 1;
    while (i <= argc &&argv[i])
    {
        if (!strcmp("-?", argv[i]) || !strcmp("-h", argv[i]))
            print_help(data);
        else if (!strcmp("-v", argv[i]))
            data->verbose = true;
        else if (!strcmp("-f", argv[i]))
            data->flood = true;
        else if (!strcmp("-n", argv[i]))
            data->numeric = true;
        else if (!strcmp("--ip-timestamp", argv[i]))
            data->ip_timestamp = true;
        else if (!strcmp("-r", argv[i]))
            data->bypass_routing = true;
        else if (!strcmp("-l", argv[i]))
        {
            if (i + 1 > argc)
            {
                print_help(data);
            }
            else if (atoi(argv[i + 1]) > 0 && atoi(argv[i + 1]) < 65536)
                data->preload = atoi(argv[i + 1]);
            else if (atoi(argv[i + 1]) != 0)
            {
                fprintf(stderr, "%s: invalid argument: '%s': out of range: 1 <= value <= 65536\n", argv[0], argv[i + 1]);
                ft_exit(data);
            }
            else
            {
                fprintf(stderr, "%s: invalid argument: '%s'\n", argv[0], argv[i + 1]);
                ft_exit(data);
            }
        }
        else if (valid_ip(argv[i]) == 1 && valid_hostname(argv[i]) == 0)
            data->ip = argv[i];
        else
        {
            fprintf(stderr, "%s: %s: Name or service not known\n", argv[0], argv[i]);
            ft_exit(data);
        }
        i++;            
    }
}

t_ping *init_struct()
{
    t_ping *data = (t_ping *)malloc(sizeof(t_ping));
    if (!data)
        ft_exit(NULL);
    bzero(data, sizeof(*data));
    data->ip = NULL;
    data->verbose = false;
    data->flood = false;
    data->numeric = false;
    data->ip_timestamp = false;
    data->bypass_routing = false;
    data->help = false;
    data->preload = -1;
    return (data);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "%s: usage error: Destination address required\n", argv[0]);
        return(1);
    }
    signal(SIGINT, handle_sigint);
    t_ping *data = init_struct();
    parse(argc, argv, data);
    send_socket(data);
    //recv_socket(data);
    return (0);
}