#include "brutuslinksys.h"



int
encode_base64(char **txt)
{
	int i = 0;

	base64_t *base64 = NULL;
	base64 = malloc(sizeof(base64_t));

	if ( base64 == NULL ) {
		fprintf(stderr, "mallc base64 failed\n");
		return -1;
	}


	base64->size = strlen(*txt);

	int a_decimal[base64->size];

	for ( i = 0; i < base64->size; i++) {
		a_decimal[i] = (int) txt[0][i];
	}

	if ( base64_conver_binary(a_decimal, base64) == -1 ) {
		base64_free(base64);
		return -1;
	}


	base64_calcul_somme_binary(base64);


	if ( base64_encode_somme(base64) == -1 ) {
		base64_free(base64);
		return -1;
	}


	memset(*txt, 0, strlen(*txt));

	strcpy(*txt, base64->encode);
	
	base64_free(base64);
	
	return 0;
}



int
base64_conver_binary(unsigned a_decimal[], base64_t *base64)
{
	int nbr = 0;
	int i;
	int i2;
	char buff[50];
	char buff_binary[2000];

	memset(buff_binary, 0, sizeof(buff_binary));

	for ( i = 0; i < base64->size; i++ ) {

		i2 = 7;
		while ( i2 > -1 ) {
			nbr =  !!(a_decimal[i] & (1u << i2));
			sprintf(buff, "%d", nbr);
			strcat(buff_binary, buff);
			memset(buff, 0, sizeof(buff));
		  	i2--;
		}

	}

	base64->binary = strdup(buff_binary);

	if ( base64->binary == NULL ) {
		fprintf(stderr, "binary strdup failed\n");
		return -1;
	}

	return 0;
}


int
base64_calcul_somme_binary(base64_t *base64)
{

	int somme = 0;
	int result = 0;
	int i, i2 = 0;
	char buff[11];
	base64->size = 0;
	base64->add = 0;


	for ( i = 0; i < strlen(base64->binary); i ) {

		for ( i2 = 0; i2 < 6; i2++ ) {

			buff[i2] = base64->binary[i+i2];

		}


		if ( i == strlen(base64->binary)-4 ) {
			strcat(buff, "00");
			base64->add = 1;
			buff[i2+3] = '\0';
		}

		else if (  i == strlen(base64->binary)-5 ) {
			strcat(buff, "000");
			base64->add = 1;
			buff[i2+4] = '\0';
		}

		else if ( i == strlen(base64->binary)-2 ) {
			strcat(buff, "0000");
			base64->add = 2;
			buff[i2+5] = '\0';
		}

		else if (  i == strlen(base64->binary)-1 ) {
			strcat(buff, "00000");
			base64->add = 2;
			buff[i2+6] = '\0';
		}

		result = 0;
		for ( i2 = strlen(buff); i2 > -1 ; i2--) {

			if ( buff[i2] != '\0' ) {

				if ( i2 == strlen(buff)-1 )
					somme = 1*1;
				else
					somme = somme*2;


				if ( buff[i2] == '1' ) {
					result += somme;
				}
			}
		}	

		base64->tab_somme[base64->size] = result;
		base64->size++;
		i = i +6;

	}


	return 0;
}


int
base64_encode_somme(base64_t *base64)
{
	char crypt[300];
	int i;

	memset(crypt, 0, sizeof(crypt));

	for ( i = 0; i < base64->size; i++ ) {

		switch ( base64->tab_somme[i] ) {

			case 0 :
				strcat(crypt, "A");
			break;
		
			case 1 :
				strcat(crypt, "B");
			break;

			case 2 :
				strcat(crypt, "C");
			break;
		
			case 3 :
				strcat(crypt, "D");
			break;

			case 4 :
				strcat(crypt, "E");
			break;
		
			case 5 :
				strcat(crypt, "F");
			break;

			case 6 :
				strcat(crypt, "G");
			break;
		
			case 7 :
				strcat(crypt, "H");
			break;

			case 8 :
				strcat(crypt, "I");
			break;
		
			case 9 :
				strcat(crypt, "J");
			break;

			case 10 :
				strcat(crypt, "K");
			break;
		
			case 11 :
				strcat(crypt, "L");
			break;

			case 12 :
				strcat(crypt, "M");
			break;
		
			case 13 :
				strcat(crypt, "N");
			break;

			case 14 :
				strcat(crypt, "O");
			break;
		
			case 15 :
				strcat(crypt, "P");
			break;

			case 16 :
				strcat(crypt, "Q");
			break;
		
			case 17 :
				strcat(crypt, "R");
			break;

			case 18 :
				strcat(crypt, "S");
			break;
		
			case 19 :
				strcat(crypt, "T");
			break;

			case 20 :
				strcat(crypt, "U");
			break;
		
			case 21 :
				strcat(crypt, "V");
			break;

			case 22 :
				strcat(crypt, "W");
			break;
		
			case 23 :
				strcat(crypt, "X");
			break;

			case 24 :
				strcat(crypt, "Y");
			break;
		
			case 25 :
				strcat(crypt, "Z");
			break;
		
			case 26 :
				strcat(crypt, "a");
			break;
		
			case 27 :
				strcat(crypt, "b");
			break;

			case 28 :
				strcat(crypt, "c");
			break;
		
			case 29 :
				strcat(crypt, "d");
			break;

			case 30 :
				strcat(crypt, "e");
			break;
		
			case 31 :
				strcat(crypt, "f");
			break;

			case 32 :
				strcat(crypt, "g");
			break;
		
			case 33 :
				strcat(crypt, "h");
			break;

			case 34 :
				strcat(crypt, "i");
			break;
		
			case 35 :
				strcat(crypt, "j");
			break;

			case 36 :
				strcat(crypt, "k");
			break;
		
			case 37 :
				strcat(crypt, "l");
			break;

			case 38 :
				strcat(crypt, "m");
			break;
		
			case 39 :
				strcat(crypt, "n");
			break;

			case 40 :
				strcat(crypt, "o");
			break;
		
			case 41 :
				strcat(crypt, "p");
			break;

			case 42 :
				strcat(crypt, "q");
			break;
		
			case 43 :
				strcat(crypt, "r");
			break;

			case 44 :
				strcat(crypt, "s");
			break;
		
			case 45 :
				strcat(crypt, "t");
			break;

			case 46 :
				strcat(crypt, "u");
			break;
		
			case 47 :
				strcat(crypt, "v");
			break;

			case 48 :
				strcat(crypt, "w");
			break;
		
			case 49 :
				strcat(crypt, "x");
			break;

			case 50 :
				strcat(crypt, "y");
			break;
		
			case 51 :
				strcat(crypt, "x");
			break;

			case 52 :
				strcat(crypt, "0");
			break;

			case 53 :
				strcat(crypt, "1");
			break;
		
			case 54 :
				strcat(crypt, "2");
			break;

			case 55 :
				strcat(crypt, "3");
			break;
		
			case 56 :
				strcat(crypt, "4");
			break;

			case 57 :
				strcat(crypt, "5");
			break;
		
			case 58 :
				strcat(crypt, "6");
			break;

			case 59 :
				strcat(crypt, "7");
			break;
		
			case 60 :
				strcat(crypt, "8");
			break;

			case 61 :
				strcat(crypt, "9");
			break;
		
			case 62 :
				strcat(crypt, "+");
			break;

			case 63 :
				strcat(crypt, "/");
			break;
		}

	}

	if ( base64->add == 1 )
		strcat(crypt, "=");

	else if ( base64->add == 2 )
		strcat(crypt, "==");


	base64->encode = strdup(crypt);

	if ( base64->encode == NULL ) {
		fprintf(stderr, "encode mlloc failed\n");
		return -1;
	}


	return 0;
}



void
base64_free(base64_t *base64)
{

	if ( base64 != NULL ) {

		if ( base64->binary != NULL ) {
			free(base64->binary);
			base64->binary = NULL;
		}

		if ( base64->encode != NULL ) {
			free(base64->encode);
			base64->encode = NULL;
		}

		free(base64);
		base64 = NULL;
	}

}

