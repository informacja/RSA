#include "header.h"

// -----------------------------------------------------------------------------

void show_info(rsa_util* rsa)
{
    num p = rsa->p, q = rsa->q, phi = rsa->phi, d = rsa->d, e = rsa->e, n = rsa->n;

    printf("\nRule: (1) = %d \ngcd(e,phi): %d\n",(e*d) % phi, gcd(e, phi) );
    printf("minimum log(e) >= log(n)/4 | %.2lf >= %.2lf", log(e) , log(n)/4);

    printf("\nq = %ld\np = %ld\n", q, p);
    printf("e = %d\n", e);
    printf("d = %d\n", d);
    printf("n = %d\n", n);
    printf("r = %d\n", phi);
}

// -----------------------------------------------------------------------------

void get_keys_to_decrypt(char argv[], num* e, num* n)
{
    if ( !file_exist(argv) )
    {
        printf("Plik: %s nie istnieje\n", argv);
        exit(ERR_FILE_N_EXIST);
    }
    puts("Podaj klucz publiczny(e): ");
    scanf("%llu", e); // celowo używam scanfa

    printf("Podaj klucz publiczny(n): ");
    scanf("%llu", n);

//    *e = 174687; *n = 488413;
}

// -----------------------------------------------------------------------------


