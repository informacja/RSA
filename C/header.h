#ifndef HEADER_H
#define HEADER_H

//#define FINAL             // without any log eg. read/save info
#define COLOR_CONSOLE     // Don't #include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "getline.h"        // get line of text function from stream

#ifdef _WIN32               // for file_exist()
 #include <io.h>                                                            // (Windows)
 /* Values for the second argument to access( , ). These may be OR'd together.  */

 #define R_OK    4       /* Test for read permission.  */
 #define W_OK    2       /* Test for write permission.  */
//#define   X_OK    1    /* execute permission - unsupported in windows */
 #define F_OK    0       /* Test for existence.  */

#else
 #include <unistd.h>      	// access(...) // sprawdza dostкp do pliku, katalogu (UNIX header)
#endif

// ----------------------------------------------------------------------------

typedef char bool;
typedef char* string;
typedef unsigned long long num;

#define NUM_OF(x) (sizeof (x) / sizeof (*x))

#define MAX_LEN 80
#define TABSIZE 255

// ----------------------------------------------------------------------------

char bufor[MAX_LEN+1] = {0};
num n; // global variable

typedef struct{
    size_t size;
    string *line;
} str_vec;

typedef struct {
    num p, q, phi, d, e, n;
} rsa_util;

enum {
    ERR_FILE_OPEN = 1,
    ERR_BAD_PTR,
    ERR_ALOC_PTR,
    ERR_E_BIGGER,
    ERR_ALOC_ZERO,
    ERR_FILE_N_EXIST
}errors;

#endif // HEADER_H
