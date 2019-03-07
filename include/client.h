#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>


#ifndef CLIENT_H_
#define CLIENT_H_

typedef struct client_s client_t;

struct client_s {
	int sock;
	struct sockaddr_in server;
	struct msg_struct *msg;
};

client_t *init_client(char *ip_addr, unsigned short port);
int send_data(client_t *client_data, char *key);

#endif
