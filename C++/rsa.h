/* Code from
    https://stackoverflow.com/questions/20111827/various-questions-about-rsa-encryption
*/

#include "header.h"

extern num n;


// ---------------------------------------------------------------

template <class T>
T mul_mod(T a, T b, T m) {
    if (m == 0) return a * b;

    T r = T();

    while (a > 0) {
        if (a & 1)
            if ((r += b) > m) r %= m;
        a >>= 1;
        if ((b <<= 1) > m) b %= m;
    }
    return r;
}

// ---------------------------------------------------------------

template <class T>
T pow_mod(T a, T n, T m) {
    T r = 1;

    while (n > 0) {
        if (n & 1)
            r = mul_mod(r, a, m);
        a = mul_mod(a, a, m);
        n >>= 1;
    }
    return r;
}

// ---------------------------------------------------------------

struct crypt : binary_function<num, num, num> {
    num operator()(num input, num key) const {
        return pow_mod(input, key, n);
    }
};

// ---------------------------------------------------------------

num prime_max79( int n = 50 )
{
    return n*n - 79*n + 1601;
}

// ---------------------------------------------------------------

template <class num>
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

template <class num>
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
    int i;
    num j = sqrt(pr);
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
        cout << "\nError func get_e(): log(e) !< log(n)/4 ";
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

// ---------------------------------------------------------------
