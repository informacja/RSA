/************************************
*                           		*
*   License: GNU GPL                 *
*   Date   : 01-02-2019              *
*   Author : Piotr Wawryka      	*
*   Email  : piotrwpwsz@gmail.com 	*
*                           		*
************************************/

#include "header.h"

#include "file.c"           // order of include matters
#include "rsa.c"
#include "dialog.c"

#ifdef COLOR_CONSOLE
#include "colors.c"
#endif // COLOR_CONSOLE

extern char bufor[];
extern num n;

// ----------------------------------------------------------------------------

int main( int argc, char * argv[] ) {

    rsa_util rsa = { 0 };
    string msg = calloc(BUFSIZ, sizeof(*msg));
    int len = 0;
    num *encrypted;

    if ( argc > 1 )                                                // jesli podano argumenty do programu
    {
        decrypt(argv[1], &rsa, &len, encrypted);
    }
    else
    {
        encrypt(msg, &rsa, &len, encrypted);
    }

    free(encrypted);
    free(msg);

    puts("\n");
    system("pause");
    return 0;
}
