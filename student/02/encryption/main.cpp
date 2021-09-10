#include <iostream>
#include <string>

using namespace std;

int main()
{
    string encryption_key = "" ;
    cout << "Enter the encryption key: ";
    cin >> encryption_key;

    // Virhetarkistus, salausavaimessa pitää olla 26 kirjainta
    if (encryption_key.length() != 26){
        cout <<"Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    // Merkkijono saa sisältää vain anglisia pienaakkosia
    for(size_t i = 0; i < encryption_key.length(); ++i){
        char char_to_check = encryption_key.at(i);
        if(char_to_check < 'a' or char_to_check > 'z'){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    // Merkkijonon pitää sisältää kaikki angliset pienaakkoset
    for(char char_to_find = 'a'; char_to_find <= 'z'; ++char_to_find){
        size_t pos = encryption_key.find(char_to_find);
        if(pos == string::npos){
            return EXIT_FAILURE;
            cout <<"Error! The encryption key must contain all alphabets a-z." << endl;
        }
    }

    // Toteutetaan tekstinsalaus
    string text_to_encrypt = "";
    cout << "Enter the text to be encrypted: ";
    cin >> text_to_encrypt;

    string::size_type text_lenght = text_to_encrypt.length();
    string encrypted_text = "";

    for(size_t i = 0; i < text_lenght; ++i){
        char uncrypted_char = text_to_encrypt.at(i);
        size_t j = uncrypted_char - 'a';  //selvitetään indeksi aakkosista ASCII-arvojen avulla
        char encrypted_char = encryption_key.at(j);
        encrypted_text += encrypted_char;
    }

    cout <<"Encrypted text: "<< encrypted_text << endl;

    return EXIT_SUCCESS;
}
