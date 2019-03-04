#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef struct client_s client_t;

struct client_s {
	int sock;
	struct sockaddr_in server;
};


client_t *init_client(char *ip_addr, unsigned short port);
int client(client_t *client_data);