#include <iostream>
#include <string>

using namespace std;

int main()
{
    string encryption_key = "" ;
    cout << "Enter the encryption key: ";
    cin >> encryption_key;

    string text_to_encrypt = "";
    cout << "Enter the text to be encrypted: ";
    cin >> text_to_encrypt;

    string::size_type text_lenght = text_to_encrypt.length();
    string encrypted_text = "";

    for(size_t i = 0; i < text_lenght; ++i){
        char uncrypted_char = text_to_encrypt.at(i);
        size_t j = uncrypted_char - 'a'; //selvitetään indeksi aakkosista ASCII-arvojen avulla
        char encrypted_char = encryption_key.at(j);
        encrypted_text += encrypted_char;
    }

    cout <<"Encrypted text: "<< encrypted_text << endl;

    return 0;
}
