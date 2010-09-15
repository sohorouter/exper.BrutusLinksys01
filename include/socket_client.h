#ifndef __SOCKET_CLIENT__
#define __SOCKET_CLIENT__


typedef struct _socket_client_s {
	int socket_cli;
	struct sockaddr_in to;
} socket_client_t;



int	socket_client_new(socket_client_t *client, const char *ip);
int	socket_client_connect(socket_client_t *client);
int	socket_client_send(int socket, const char *txt);
int	socket_client_recv(int socket, char **txt);
void	socket_client_free(socket_client_t *client);


#endif /* __SOCKET_CLIENT__ */

