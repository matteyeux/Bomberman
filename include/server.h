#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
extern int sock;

struct msg_struct {
	int id;
	char key[10];
};


typedef struct net_data_s net_data_t;

struct net_data_s {
	int client_sock;
	struct sockaddr_in client;
	unsigned int client_addr_len;
	struct msg_struct *message;
};


int init_server(unsigned short port);
void *handler(void *input);