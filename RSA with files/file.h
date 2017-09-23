
#include "header.h"

// -----------------------------------------------------------------------------------

void wczytajPlik( string nazwaPliku, string &dest )
{
    std::ifstream plik;
    plik.open( nazwaPliku.c_str() );
    if( !plik.good() )
    {
        cout << "\nBłąd otwarcia pliku: " << nazwaPliku << endl;
        system("pause");
        exit(1);
    }

    while( !plik.eof() )
        {
            getline( plik, dest );
            cout << dest << endl;
        }
}

// -----------------------------------------------------------------------------------

void save_file( string nazwaPliku, string &src )
{
     ofstream out(nazwaPliku, ios::out | ios::binary);

    if(!out) {
        cout << "Nie mogę otworzyć pliku do zapisu.\n";
        system("pause");
        exit(2);
    }
//    std::copy(
//        std::istreambuf_iterator<char>(src),
//        std::istreambuf_iterator<char>( ),
//        std::ostreambuf_iterator<char>(out));
//streamsize = strlen()
    out.write(src.c_str(),(streamsize) strlen(src.c_str()));
//    out << src;
    cout << "Zapisano do: " << nazwaPliku << "\t" << src << endl;
    out.close();
}

// -----------------------------------------------------------------------------------

void load_file( string file_name, string &src )
{
//    std::ifstream input( file_name, std::ios::binary );
////
//     std::vector<char> buffer((
//            std::istreambuf_iterator<char>(input)),
//            (std::istreambuf_iterator<char>()));
////
//     std::copy(
//        std::istreambuf_iterator<char>(input),
//        std::istreambuf_iterator<char>( ),
//        std::ostreambuf_iterator<char>(src));

    std::ifstream ifs( file_name, std::ios::binary );
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );
    src = content;

    cout << "Odczytano z pliku: " << file_name << "\t" << src << endl;
// -----------------------------------------------
//    std::ifstream file( file_name );
//    std::string str;
//    std::string file_contents;
//    while (std::getline(file, str))
//    {
//      file_contents += str;
//      file_contents.push_back('\n');
//    }
//    src = file_contents;
}

// -----------------------------------------------------------------------------------




void save_file( string nazwaPliku, vector<num> &src )
{
     ofstream out(nazwaPliku, ios::out | ios::binary);

    if(!out) {
        cout << "Nie mogę otworzyć pliku do zapisu.\n";
        system("pause");
        exit(2);
    }
    for( int i = 0; i < src.size(); i++ )
    {
        out << src[i] << endl;
        cout << "Save: " << src[i] << endl;
    }


//    cout << "Zapisano do: " << nazwaPliku << "\t" << src << endl;
    out.close();
}

// -----------------------------------------------------------------------------------

void load_file_as_num( string nazwaPliku, vector<num> &encrypted )
{
    ifstream infile(nazwaPliku, ios::in | ios::binary);

    num buff;

    while (infile >> buff)
        encrypted.push_back(buff);




//       while( !out.eof() )
//        {
//            encrypted.push_back (myint);
//            getline( plik, dest );
//            cout << dest << endl;
//        }
}

// -----------------------------------------------------------------------------------

bool FileExist( const std::string& name )
{
     std::ifstream f(name.c_str());  // New enough C++ library will accept just name
     return f.is_open();
}

// -----------------------------------------------------------------------------------


// -----------------------------------------------------------------------------------

