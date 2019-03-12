#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
extern int sock;

struct msg_struct {
	int id;
	char key[10];
};

typedef struct server_data_s server_data_t;

struct server_data_s {
	int sock_fd;
	struct sockaddr_in client;
	unsigned int client_addr_len;
};

int init_server(unsigned short port);
void *handler(void *input);