#include "xor_cipher.h"

xor_cipher::xor_cipher()
{
    opend_file_in_bits = nullptr;
}

xor_cipher::~xor_cipher()
{
    if(opend_file_in_bits!=nullptr)
        delete opend_file_in_bits;

}

string xor_cipher::key_generator()
{
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(0,1);

    string key;

    if(opend_file_in_bits==nullptr){
        return "";
    }
    else{
        unsigned int z;

    for(unsigned int i=0;i<opend_file_in_bits->length();i++){
        z=distribution(generator);
        key+=to_string(z);

    }

    return key;
    }
}


string * xor_cipher::read_bits(fstream *file) //#
{
    string *bits = new string;
    char bit;

    while(file->get(bit)){
        *bits+=static_cast<bitset<8>>(static_cast<unsigned char>(bit)).to_string();
        }
        qDebug() << "eldo";
        file->close();
        return bits;
}

void xor_cipher::cipher(string key,const string name,const string path_to_save ) //#
{


    string result_str;
    bitset<8> result_bit;
    const bitset<32> mark_bits = static_cast<bitset<32>>(mark);



    int bit_long_local= opend_file_in_bits->length();
    qDebug() << "ww "<<bit_long_local;

    for(unsigned long long i=0; i<bit_long_local;i+=8)
       {
            result_bit=static_cast<bitset<8>>(opend_file_in_bits->substr(i,i+8)) ^ static_cast<bitset<8>>(key.substr(i,i+8));
            result_str+=result_bit.to_string();
       }
    qDebug() << "ww";

    bitset<8> key_position(result_str.length());
    result_str+=key;
    result_str.insert(0,mark_bits.to_string());
    qDebug() <<QString::fromStdString(result_str.substr(0,31));


    from_bits_to_file(path_to_save, result_str,name);

}

void xor_cipher::decipher(const string name,const string path_to_save)
{

    string result_str;
    bitset<8> result_bits;
    bitset<32> mark_bits = static_cast<bitset<32>>(opend_file_in_bits->substr(0,32));
    qDebug() <<QString::fromStdString(opend_file_in_bits->substr(0,32));
    qDebug() <<static_cast<int32_t>(mark_bits.to_ulong())<<mark;
    if(static_cast<int32_t>(mark_bits.to_ulong())==mark)
    {
        string file_bits = opend_file_in_bits->substr(32);
        int key_length = file_bits.length()/2;

        string key = file_bits.substr(0,key_length);
        string encoded_file = file_bits.substr(key_length);

    for(unsigned int i=0; i<encoded_file.length();i+=8)
    {
        result_bits=static_cast<bitset<8>>(key.substr(i,i+8))^static_cast<bitset<8>>(encoded_file.substr(i,i+8));
        result_str+=result_bits.to_string();
    }

    from_bits_to_file(path_to_save, result_str, name);

    }
    else
    {
        throw invalid_argument("Probably file was not encrypted");
    }

}

bool xor_cipher::load_file(const string path_to_file)
{
    fstream *f= new fstream;
    f->open(path_to_file.c_str(),ios_base::binary | ios_base::in);

    if(!f->is_open()){
        delete  f;
        return false;
    }
    else{
        opend_file_in_bits = read_bits(f);
        delete f;
        return true;
    }
}

void xor_cipher::from_bits_to_file( string path_to_save, const string file_string, string file_name) //#
{

    file_name.insert(0,"Ci_");
    path_to_save+="\\";
    path_to_save+=file_name;

    fstream file;
    file.open(path_to_save.c_str(), ios::binary | ios::out);

    unsigned char result_bit_char;


    qDebug() << file_string.length();
    for(unsigned long long int i=0; i<file_string.length();i+=8)
        {
            result_bit_char=static_cast<bitset<8>>(file_string.substr(i,i+8)).to_ulong();
            file.put(result_bit_char);
        }

    file.close();
}
