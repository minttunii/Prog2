/* Ristinolla
 *
 * Kuvaus:
 *   Ohjelma toteuttaa ristinollapelin, jossa pelialuetta pystyy
 * laajentamaan. Alussa peliruudukko on kooltaan 3 x 3. Peliruudukossa
 * on kolmenlaisia merkkejä: risti (X), nolla (0) ja tyhjä (.).
 *   Pelivuorossa ovat vuorotellen risti ja nolla, risti aloittaa.
 * Joka kierroksella vuorossa olevalle merkille kysytään koordinaatteja
 * eli kahta lukua. Vuorossa oleva merkki sijoitetaan peliruudukolla
 * annettuihin koordinaatteihin, ja vuoro siirtyy toiselle merkille.
 *   Pelin voittaa merkki, jolla saadaan ensimmäiseksi täytettyä peliruudukon
 * kokonainen rivi, kokonainen sarake tai kokonainen diagonaali.
 * Peli voi päättyä myös sellaiseen tilanteeseen, että peliruudukko on
 * täynnä merkkejä, mutta kumpikaan merkki ei voittanut.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, tai koordinaatit saavat ylittyä tai alittua
 * korkeintaan yhdellä. Jos annettu x- tai y-koordinaatti (rivi tai sarake)
 * ylittyy yhdellä, peliruudukko laajenee oikealle ja alaspäin. Jos taas
 * x- tai y-koordinaatti alittuu yhdelle, peliruudukko laajenee vasemmalle
 * ja alaspäin. Peliruudukko siis pysyy aina neliön muotoisena.
 *   Pelin päättyessä kerrotaan, kumpi voitti, vai voittiko kumpikaan.
 *
 * Ohjelman kirjoittaja
 * Nimi: Minttu Niirane
 * Opiskelijanumero: 291834
 * Käyttäjätunnus: pqmini
 * E-Mail: minttu.niiranen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */


#include <iostream>
#include <vector>
#include <string>
#include <cctype>

namespace  {
    const int DEFAULT_SIZE = 3;
}

// Funktio muodostaa halutun kokoisen peliruudukon pelin alkaessa
void make_grid(std::vector< std::vector<char> >& grid, size_t n){

    for(size_t column = 0; column < n; ++column){
        std::vector<char> column_vector(n, '.');
        grid.push_back(column_vector);
    }
}

// Funktio tulostaa pelilaudan
void print_grid(std::vector< std::vector<char> >& grid){

    // Tulostetaan x-akselin numerot tauluun
    std::cout << "  ";
    for(size_t x = 0; x < grid.size(); ++x){
        std::cout << (x + 1) % 10 << ' ';
    }
    std::cout << std::endl;

    // Tulostetaan y-akselin numerot ja loput taulusta riveittäin
    for(size_t y = 0; y < grid.size(); ++y){
        std::cout << (y + 1) % 10 << ' ';
        for(size_t x = 0; x < grid.size(); ++x){
            std::cout << grid.at(y).at(x) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Funktio selvittää vuorossa olevan pelaajan ja palauttaa nimen
std::string player_in_turn(int player_turn){
    std::string player_name = "";

    if(player_turn % 2 != 0){
        player_name = "X";
    }
    else{
        player_name = "0";
    }
    return player_name;
}


// Funktio tarkistaa käyttäjän antaman syötteen oikeellisuuden
bool check_input(std::string x, std::string y,
                 std::vector< std::vector<char> >& grid){

    // Koordinaattien pitää olla lukuja
    if(! std::isdigit(x.at(0)) or ! std::isdigit(y.at(0))){
        std::cout << "Coordinate outside the board" << std::endl;
        return false;
    }

    // Koordinaattien pitää olla pelilaudalla, tai mennä vain yhdellä ali/yli
    int x1 = std::stoi(x); int y1 = std::stoi(y);
    size_t x2 = std::stoi(x); size_t y2 = std::stoi(y);

    if(x1 < 0 or x2 > (grid.size() + 1) or y1 < 0 or
            y2 > (grid.size() + 1)){
        std::cout << "Coordinate outside the board" << std::endl;
        return false;
    }
    // Koordinaatit ei voi ylittyä ja/tai alittua samaan aikaan
    if((x1 <= 0 and y1 <= 0) or
            (x2 >= (grid.size() + 1) and y2 >= (grid.size() + 1))
            or (x1 <= 0 and y2 >= grid.size()) or
            (y1 <= 0 and x2 >= grid.size())){
        std::cout << "Coordinate outside the board" << std::endl;
        return false;
    }

    // Peliruudun pitää olla vapaana
    if(grid.at(std::stoi(x)).at(std::stoi(y)) != '.'){
        std::cout << "The given place is already occupied" << std::endl;
        return false;
    }
    return true;
}


// Funktio kysyy ja lukee koordinaatit
void read_coordinates(std::vector< std::vector<char> >& grid){
    std::cout << "Start game:" << std::endl;
    print_grid(grid);

    int player_turn = 1;
    std::string x = "";
    std::string y = "";

    while(true){
        std::cout << "For " << player_in_turn(player_turn) <<
                     ", enter coordinates: x y> ";
        std::cin >> x;

        // Tarkistetaan ensin, onko ensimmäinen syöte lopetuskomento
        if(x == "q"){
            std::cout << "Why on earth you are giving up the game?" << std::endl;
            return;
        }
        std::cin >> y;

        //Syötettä luetaan kunnes se kelpaa
        if(check_input(x, y, grid)){
            break;
        }
    }
    ++player_turn;
}


int main()
{
    std::vector< std::vector<char> > grid = {};
    make_grid(grid, DEFAULT_SIZE);
    read_coordinates(grid);



    return 0;
}
