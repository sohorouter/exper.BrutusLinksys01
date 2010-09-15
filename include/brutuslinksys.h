#ifndef __BRUTUSLINKSYS__
#define __BRUTUSLINKSYS__



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include "config.h"
#include "socket_client.h"
#include "base64.h"


void	welcome(void);
int	send_and_recv_header(const char *ip, mode_t mode, char **header, char *txt);
int	router(const char *ip, const char *login, const char *name_file);
int	brutus(const char *login, const char *name_file, const char *ip);
char*	build_header(mode_t mode, const char *base64_txt);
int	type_router_check(const char *ip);


#endif /* __BRUTUSLINKSYS__ */

