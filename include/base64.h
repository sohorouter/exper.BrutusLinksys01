#ifndef __BASE64__
#define __BASE64__


typedef struct _base64_s {
	char *binary;
	int tab_somme[200];
	size_t size;
	char *encode;
	int add;
} base64_t;


int	encode_base64(char **txt);
int	base64_conver_binary(unsigned a_decimal[], base64_t *base64);
int	base64_encode_somme(base64_t *base64);
void	base64_free(base64_t *base64);

#endif /* __BASE64__ */

