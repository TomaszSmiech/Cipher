#ifndef XOR_CIPHER_H
#define XOR_CIPHER_H
#include<iostream>
#include<fstream>

#include<cstdio>
#include<cstdlib>
#include<string>
#include<bitset>
#include<limits>
#include <random>
#include <stdexcept>
#include <QDebug>


using namespace std;
class xor_cipher
{
    private:

        const int32_t mark{815587961};
        string * opend_file_in_bits;
        string * read_bits(fstream *);
        void from_bits_to_file( string path_to_save, const string file_string, string file_name);

    public:
        xor_cipher();
        ~xor_cipher();
        void cipher( string key,const string name,const string path_to_save ="");
        void decipher(const string name, const string path_to_save ="");
        bool load_file(const string);
        string key_generator();
    protected:

};

#endif // XOR_CIPHER_H
