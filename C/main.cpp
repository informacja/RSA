
#include "header.h"
#include "file.c"
#include "rsa.c"
#include "colors.c"

 num n; // global variable

// ---------------------------------------------------------------

void setup( num &p, num &q );

int main( int argc, char * argv[] ) {

    num p = 0, q = 0, phi = 0, d = 0, e = 0;
    string msg = "Secret Messages!";

    if ( argc > 1 )     // podano argumenty do programu
    {
        if ( !FileExist( argv[1] ) )
        {
            cout << "Plik: " << argv[1] << " \tnie istnieje\n";
            exit(6);
        }

        cout << "Podaj klucz publiczny(e): ";
        cin >> d;
        cout << "Podaj klucz publiczny(n): ";
        cin >> n;
    }
    else
    {
        setup( p, q );  // losowanie liczb pierwszych

        cout << "\nPodaj wiadomosc: ";
        getline(cin, msg);

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
        cout << "ERROR: ( e >= n ) wylosuj ponownie" << e << "\t" << n;
        system("pause");
        return 0;
    }

    d = find_inverse( e, phi );

    cout << "\nRule: (1) = " << (e*d) % phi << "\ngcd(e,phi): "<< gcd (e, phi) <<  endl;
    cout << "minimum log(e) >= log(n)/4 : " << log(e) << "\t" << log(n)/4;
}
    cout << "\nq = " << q << "\np = " << p << endl;
    cout << "e = " << e << endl;
    cout << "d = " << d << endl;
    cout << "n = " << n << endl;
    cout << "r = " << phi << endl;


    vector<num> encrypted;

    if ( argc > 1 ) // rozszyfruj txt
    {
        msg = "";
        load_file_as_num( argv[1], encrypted );

        copy( encrypted.begin(), encrypted.end(), ostream_iterator<num>(cout, "\n") );

        transform(encrypted.begin(), encrypted.end(),
                                  back_inserter(msg),
                                bind2nd(crypt(), d));

        save_file( "decrypted.txt", msg );

    }
    else            // zaszyfruj wprowadzony tekst
    {
        transform(msg.begin(), msg.end(),
                back_inserter(encrypted),
                    bind2nd(crypt(), e));

        string buff( encrypted.begin(), encrypted.end() );
        save_file( "encrypted.txt", encrypted );

        cout << "\nKlucz prywatny ( e, n ): " << e << " " << n;
        cout << "\nKlucz publiczny( d, n ): ";
        setIntensity();
        cout << d << " " << n;
        setNormal();
    }

    cout << "\n";
    system("pause");

    return 0;
}

void setup( num &p, num &q )
{
    srand( time(NULL) );                    // wymagane do dzia?ania losowo?ci

    p = prime_max79( rand() %80 );      // minimalna liczba pierwsza to 11
    q = prime_max79( rand() %80 );

    while( p == q )
    {
        num q = prime_max79( rand() %80 );
    }
}
