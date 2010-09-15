#include "brutuslinksys.h"


int
socket_client_new(socket_client_t *client, const char *ip)
{

	client->socket_cli = socket(AF_INET, SOCK_STREAM, 0);

	if ( client->socket_cli == -1 ) {
		printf("function socket() failed\n");
		return -1;
	}


	client->to.sin_family = AF_INET;
	client->to.sin_port = htons(PORT);
	client->to.sin_addr.s_addr = inet_addr(ip);

	return 0;
}



int
socket_client_connect(socket_client_t *client)
{
	int ret;

	ret = connect(client->socket_cli, (struct sockaddr *)&client->to, sizeof(client->to));

	if ( ret == -1 ) {
		printf("connect() failed\n");
		return -1;
	}

	return 0;
}


int
socket_client_send(int socket, const char *txt)
{
	int ret;

	ret = write(socket, txt, strlen(txt));

	if ( ret == -1 ) {
		printf("write socket failed\n");
		return -1;
	}

	return 0;
}


int
socket_client_recv(int socket, char **txt)
{
	int ret;

	ret = read(socket, *txt, 2000);

	if ( ret == -1 ) {
		printf("read socket_cli failed\n");
		return -1;
	}

	return 0;
}


void
socket_client_free(socket_client_t *client)
{

	if ( client!= NULL ) {

		if ( client->socket_cli != -1 )
			close(client->socket_cli);

		free(client);
		client = NULL;

	}

}

