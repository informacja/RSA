/* https://stackoverflow.com/questions/20111827/various-questions-about-rsa-encryption */
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>
#include <time.h>

using namespace std;

typedef unsigned long long num;

//const num e = 65537;
//const num d = 38110914516113;
 num n;

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

      while(e<phi){                   // wyznacza poprawnie e
        num count = gcd(e,phi);
        if(count==1)
            break;
        else
            e++;
        }
    return e;
}
// ---------------------------------------------------------------

int main() {

    srand( time(NULL) );                    // wymagane do działania losowości

    num p = prime_max79( rand() %80 );
    num q = prime_max79( rand() %80 );

    p = 9999991;
    q = 11999989;

    n = p * q;
    num phi = (p-1)*(q-1);      // 'phi' is also known as 'r'

    num bigger_prime = ( (p < q) ? q : p );
    num e = (llrand() % (n - bigger_prime + 1) ) + bigger_prime;       // e (exponent, wykladnik) = (max(p,q)+1,n)
//        e = llrand() % phi;       // e (exponent, wykladnik) = (max(p,q)+1,n)
//
     e = get_e( sqrt( bigger_prime ) * log ( bigger_prime ), phi );

    if ( e % 2 == 0 )   // otrzymujemy nieparzystą
        e++;

    int needed_to_prime = 0;

    while ( !is_prime(e) )
    {
        e += 2;
        needed_to_prime++;      // debug
    }
    cout << "DODANO : " << needed_to_prime << endl;

    if ( e >= n )
    {
        cout << "ERROR: ( e >= n ) wylosuj ponownie";
        return 0;
    }






// e = 65537;
//      double k = 2;
//
//     num d = (1 + (k*phi));
//    num a = 2;
//    d = find_inverse( a, phi );
    num d = find_inverse( e, phi );
//    const num n = p * q;

    cout << "q = " << q << "\np = " << p << endl;
    cout << "e = " << e << endl;
    cout << "d = " << d << endl;
//    cout << "n = " << n << endl;
//    cout << "r = " << phi << endl;
    cout << "\nRule: (1) = " << (e*d) % phi << "\ngcd(e,phi): "<< gcd (e, phi) <<  endl;
    cout << "minimum log(e) >= log(n)/4 : " << log(e) << "\t" << log(n)/4  << endl;


    string msg = "Very Secret Messages!¹";
    vector<num> encrypted;

    transform(msg.begin(), msg.end(),
        back_inserter(encrypted),
        bind2nd(crypt(), e));

    copy(encrypted.begin(), encrypted.end(), ostream_iterator<num>(cout, "\n"));

    cout << "\n";

    transform(encrypted.begin(), encrypted.end(),
        ostream_iterator<char>(cout, ""),
        bind2nd(crypt(), d));
    cout << "\n";

    return 0;
}
