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

struct crypt : binary_function<num, num, num> {
    num operator()(num input, num key) const {
        return pow_mod(input, key, n);
    }
};

num prime_max79( int n = 50 )
{
    return n*n - 79*n + 1601;
}

template <class num>
num gcd(num a, num b) {
    num r;
    while (b > 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

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

int main() {

    srand( time(NULL) );

    num p = prime_max79( rand() %80 );
    num q = prime_max79( rand() %80 );
    p = 9999991;
    q = 11999989;
    num phi = (p-1)*(q-1);

     num e = gcd (e, phi);
//     e = 1 (mod r) / d
//    while(e<phi){
//    num count = gcd(e,phi);
//    if(count==1)
//        break;
//    else
//        e++;
//    }

      double k = 2;

     num d = (1 + (k*phi));
    num a = 2;
    d = find_inverse( a, phi );
    const num n = p * q;

    cout << q << "\t" << p << endl;
    cout << "e = " << e << endl;
    cout << "d = " << d << endl;
    cout << "n = " << n << endl;

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
