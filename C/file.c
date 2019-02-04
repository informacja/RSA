#include "header.h"

extern char bufor[];

// -----------------------------------------------------------------------------

void save_file( string file_name, num src[], int size, bool binary )
{
     string flag = "w";
     if (binary) flag = "wb";

     FILE *fp = fopen(file_name, flag);

     if( fp == NULL )
        exit(ERR_FILE_OPEN);

     if(binary)
        fwrite(src,sizeof(src[0]),size,fp);                                     // write 10 bytes from our buffer
     else
         for (int i = 0; i < size; i++)
            fputc(src[i], fp);

     fclose(fp);

    fprintf(stdout, "Zapisano do: %s\n", file_name);

}

// -----------------------------------------------------------------------------

num* load_file_as_num( string file_name, num *encrypted, int *size )
{
    FILE *fp = fopen(file_name, "rb");

//    if(encrypted == NULL)
//        exit(ERR_BAD_PTR);

    if( fp == NULL)
       exit(ERR_FILE_OPEN);

    fseek(fp, 0L, SEEK_END);
    size_t fs = ftell(fp);                                                      // file_size
    fseek(fp, 0L, SEEK_SET);

    *size = fs/sizeof(*encrypted);
    if( *size < 1 )
        exit(ERR_ALOC_ZERO);

    encrypted = calloc(*size, sizeof(*encrypted));
    if(encrypted == NULL)
        exit(ERR_ALOC_PTR);

    fread(encrypted,sizeof(*encrypted),*size,fp);                              // read 10 bytes to our buffer

    fclose(fp);

    return encrypted;
}

// -----------------------------------------------------------------------------

bool file_exist( const string name )
{
//    printf("%d",_access_s( name, F_OK ));
     return !_access_s( name, F_OK );
}

// -----------------------------------------------------------------------------

/*
// * old C++  code // deprecated
void save_file( string nazwaPliku, string *src )
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

void load_file( string file_name, string *src )
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

// -----------------------------------------------------------------------------



void wczytaj_plik( string nazwaPliku, string *dest )
{
    FILE *fp;

    if( (fp = fopen( nazwaPliku, "r")) == NULL)
    {
        fprintf(stderr, "\nBlad otwarcia pliku: %s", nazwaPliku );
        system("pause");
        abort();
//        exit(1);
    }

   string line = NULL;
       size_t len = 0;
       ssize_t read;


//       str_vec vec;
//       vec.size = 0;

       while ((read = getline(&line, &len, fp)) != -1) {
//           printf("Retrieved line of length %zu:\n", read);
           printf("len:%d %s\n", read, line);
       }

//       fclose(fp);
       if (line)
           free(line);
//       exit(EXIT_SUCCESS);


//    while( !plik.eof() )
//    {
//        getline( plik, dest );
//        cout << dest << endl;
//    }
//    if((bytes_read = _read(filehandle, buffer, 80)) != -1)
//    {
//        printf("Liczba bajtow przeczytanych: %d\n", bytes_read);
//        printf("Przeczytane bajty:\n%s\n", buffer);
//    }
//    else
//    {
//        printf("\nBlad podczas czytania z pliku: %s\n", fname);
//    }


    fclose(fp);
}

*/
// -----------------------------------------------------------------------------------

