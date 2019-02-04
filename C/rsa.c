/* Code from
    https://stackoverflow.com/questions/20111827/various-questions-about-rsa-encryption
*/

#include "header.h"

extern num n;


// ---------------------------------------------------------------

//template <class T>
num mul_mod(num a, num b, num m) {
    if (m == 0) return a * b;

    num r = 0;// = T();

    while (a > 0) {
        if (a & 1)
            if ((r += b) > m) r %= m;
        a >>= 1;
        if ((b <<= 1) > m) b %= m;
    }
    return r;
}

// ---------------------------------------------------------------

//template <class num>
num pow_mod(num a, num n, num m) {
    num r = 1;

    while (n > 0) {
        if (n & 1)
            r = mul_mod(r, a, m);
        a = mul_mod(a, a, m);
        n >>= 1;
    }
    return r;
}

// ---------------------------------------------------------------

num prime_max79( int n )
{
    return n*n - 79*n + 1601;
}

// ---------------------------------------------------------------

//template <class num>
num gcd(num a, num b) {   //  Greatest common divisor, Najwiekszy wspolny dzielnik
    num r;
    while (b > 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// ---------------------------------------------------------------

//template <class num>
num find_inverse(num a, num p) {
    num g, z;

    if (gcd(a, p) > 1) return 0;

    z = 1;

    while (a > 1) {
        z += p;
        if ((g=gcd(a, z))> 1) {
            a /= g;
            z /= g;
        }
    }
    return z;
}

// ---------------------------------------------------------------

num llrand()                // zwykły rand zwracał zbyt małe (4 cyfrowe) wartosci
{
    num r = 0;

    for (int i = 0; i < 5; ++i)
        r = (r << 15) | (rand() & 0x7FFF);

    return r & 0xFFFFFFFFFFFFFFFFULL;
}

// ---------------------------------------------------------------

int is_prime(num pr)      // sprawdzamy czy parametr jest liczbą pierwszą
{
    num i, j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

// ---------------------------------------------------------------
num get_e( num e, num phi )
{
     while ( log(e) < log(n)/4  )    // zabezpieczenie
    {
        e++;
        puts("\nError func get_e(): log(e) !< log(n)/4 ");
    }

        while( e < phi )    // wyznacza poprawnie e
        {
            num count = gcd( e, phi );
            if( count == 1 )
                break;
            else
                e++;
        }

        if ( e % 2 == 0 )   // otrzymujemy nieparzystą
            e++;

        int needed_to_prime = 0;

        while ( !is_prime(e) )
        {
            e += 2;
            needed_to_prime++;      // debug
        }
//        cout << "DODANO : " << needed_to_prime << endl;

    return e;
}

// -----------------------------------------------------------------------------

void setup( num *p, num *q )                        // ustaw domyslne wartosci liczb pierwszych
{
    srand( time(NULL) );                            // wymagane do dzialania losowosci

    *p = prime_max79( rand() %80 );                 // minimalna liczba pierwsza to 11 (jedenasce)
    *q = prime_max79( rand() %80 );

    while( *p == *q )
    {
        *q = prime_max79( rand() %80 );
    }
}

// -----------------------------------------------------------------------------

void calc_rsa(string msg, rsa_util* rsa )
{
    num p = rsa->p, q = rsa->q, phi = rsa->phi, d = rsa->d, e = rsa->e, n = rsa->n;

    setup( &p, &q );  // losowanie liczb pierwszych
    //            q = 1447; p = 503;    // defaults

    printf("\nPodaj wiadomosc: ");
    fgets( msg, BUFSIZ, stdin) ;
//    strcpy_s(msg, BUFSIZ, bufor);

    n = p * q;
    phi = (p-1)*(q-1);      // 'phi' is also known as 'r'

    num bigger_prime = ( (p < q) ? q : p );
    e = (llrand() % (n - bigger_prime + 1) ) + bigger_prime;       // e (exponent, wykladnik) = (max(p,q)+1,n)
    //        e = llrand() % phi;       // e (exponent, wykladnik) = (max(p,q)+1,n)
    //
    e = get_e( sqrt( bigger_prime ) * log ( bigger_prime ), phi ); // TO DO: now theres no randomize, make it
    //    e = get_e( e/sqrt(e), phi );      // dont work for big numbers

    p = q = 0; // niszczymy wartosci liczb pierwszych


    if ( e >= n )
    {
        printf("ERROR: ( e >= n ) wylosuj ponownie %llu\t%llu", e, n);
        system("pause");
        exit(ERR_E_BIGGER);
    }

    d = find_inverse( e, phi );

    rsa->d = d; rsa->e = e; rsa->p = p; rsa->phi = phi; rsa->q = q; rsa->n = n;
#ifndef FINAL
    show_info( rsa );
#endif
}


// -----------------------------------------------------------------------------

void decrypt(string argv, rsa_util* rsa, int *len, num* encrypted)
{

    get_keys_to_decrypt( argv, &rsa->d, &rsa->n);

    encrypted = load_file_as_num(argv, encrypted, len);

    for (int i = 0; i < *len; i++){
        printf("wartosc odczytana: %llu \n", encrypted[i] );

        encrypted[i] = pow_mod(encrypted[i], (*rsa).d, (*rsa).n);

        printf("wartosc odszyfrowana: %llu \n", encrypted[i] );
    }
    save_file("decrypted.txt", encrypted, *len, 0);

}

// ---------------------------------------------------------------

void encrypt(string msg, rsa_util* rsa, int *len, num* encrypted)
{
    calc_rsa(msg, rsa );

    *len = strlen(msg);
    encrypted = calloc(*len, sizeof(*encrypted));

    if(encrypted==NULL)
        exit(ERR_ALOC_PTR);

    for (int i = 0; i < *len; i++)
    {
        encrypted[i] = pow_mod((char)msg[i], (*rsa).e, (*rsa).n);
#ifndef FINAL
        printf("Wartosc zaszyfrowana: %d \n", encrypted[i] );
#endif
    }
    save_file( "encrypted.bin", encrypted, *len, 1);

    printf("\nKlucz prywatny ( e, n ): %llu %llu", (*rsa).e, (*rsa).n);    
    printf("\nKlucz publiczny( d, n ): ");
#ifdef COLOR_CONSOLE
    setIntensity();
#endif
    printf("%llu %llu", (*rsa).d, (*rsa).n);
#ifdef COLOR_CONSOLE
    setNormal();
#endif
}
