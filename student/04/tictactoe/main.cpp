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

    for(size_t i = 0; i < n; ++i){
        std::vector<char> vector(n, '.');
        grid.push_back(vector);
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

// Funktio laajentaa pelilautaa sallittuun suuntaan
void expand_board(std::vector< std::vector<char> >& grid,
                  size_t x1, size_t y1){

    size_t n = grid.size();

    // Laajeneminen alaspäin ja oikealle
    if(x1 == (grid.size() + 1) || y1 == (grid.size() + 1)){
        for(size_t i = 0; i < n ; ++i){
            grid.at(i).push_back('.');
        }
        std::vector<char> vector((n +1), '.');
        grid.push_back(vector);
    }

    //Laajeneminen ylöspäin ja vasemmalle
    if((x1 == 0 || y1 == 0)){
        std::vector< std::vector<char> > empty_grid = {};
        make_grid(empty_grid, (n+1));

        for(size_t i = 1; i <= n; ++i){
            for(size_t j = 1; j <= n; ++j){
                empty_grid.at(i).at(j) = grid.at(i-1).at(j-1);
            }
        }
        grid = empty_grid;
    }
}

// Funktio tarkistaa käyttäjän antaman syötteen oikeellisuuden
bool check_input(std::string x, std::string y,
                 std::vector< std::vector<char> >& grid){

    // Koordinaattien pitää olla lukuja
    for(char i: x){
        if(! std::isdigit(i)){
            std::cout << "Coordinate outside the board" << std::endl;
            return false;
        }
    }
    for(char i: y){
        if(! std::isdigit(i)){
            std::cout << "Coordinate outside the board" << std::endl;
            return false;
        }
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
    if((x1 < 0 and y1 < 0) or
            (x2 > (grid.size() + 1) and y2 > (grid.size() + 1))
            or (x1 <= 0 and y2 >= grid.size()) or
            (y1 <= 0 and x2 >= grid.size())){
        std::cout << "Coordinate outside the board" << std::endl;
        return false;
    }

    //Tarkistetaan, pitääkö pelilautaa laajentaa
    if(x2 == (grid.size() + 1) || y2 == (grid.size() + 1)|| x2 == 0 || y2 == 0){
        expand_board(grid, x2, y2);
        return true;
    }

    // Peliruudun pitää olla vapaana
    if(grid.at(y1 - 1).at(x1 - 1) != '.'){
        std::cout << "The given place is already occupied" << std::endl;
        return false;
    }
    return true;
}

// Funktio käy läpi ja tarkastaa eri voittotilanteet
bool check_for_winner(std::vector< std::vector<char> >& grid, int player_turn){
    size_t count_h = 0;
    size_t count_v = 0;
    size_t count_d = 0;

    for(size_t i = 0; i < (grid.size()); ++i){
        // Voitto rivillä
        count_h = 0;
        for(size_t j = 0; j < (grid.size() - 1); ++j){
            if(grid.at(i).at(j) != grid.at(i).at(j+1) || grid.at(i).at(j) == '.'){
                break;
            }
            ++count_h;
        }
        if(count_h == (grid.size()-1)){
            if(player_in_turn(player_turn + 1) == "X"){
                std::cout << "Cross won horizontally"<< std::endl;
            }
            else{
                std::cout << "Nought won horizontally"<< std::endl;
            }
            std::cout << "Game over!" << std::endl;
            return true;
        }

        // Voitto sarakkeella
        count_v = 0;
        for(size_t k = 0; k < (grid.size() - 1); ++k){
            if(grid.at(k).at(i) != grid.at(k+1).at(i) || grid.at(k).at(i) == '.'){
                break;
            }
            ++count_v;
        }
        if(count_v == (grid.size()-1)){
            if(player_in_turn(player_turn + 1) == "X"){
                std::cout << "Cross won vertically"<< std::endl;
            }
            else{
                std::cout << "Nought won vertically"<< std::endl;
            }
            std::cout << "Game over!" << std::endl;
            return true;
        }
        }

    // Voitto diagonaalilta
    for(size_t m = 0; m < (grid.size()-1); ++m){
        if(grid.at(m).at(m) != grid.at(m+1).at(m+1) || grid.at(m).at(m) == '.'){
            break;
        }
        ++count_d;
    }
    if(count_d == (grid.size() -1)){
            if(player_in_turn(player_turn + 1) == "X"){
                std::cout << "Cross won diagonally"<< std::endl;
             }
             else{
                std::cout << "Nought won diagonally"<< std::endl;
             }
             std::cout << "Game over!" << std::endl;
             return true;
     }

    // Voitto toiselta diagonaalilta
    count_d = 0;
    for(size_t m = 0; m < (grid.size()-1); ++m){
        size_t g = grid.size() - 1; // Lyhennetään lauseketta
        if(grid.at(g - m).at(m) != grid.at(g - (m + 1)).at(m + 1)
                || grid.at(g - m).at(m) == '.'){
            break;
        }
        ++count_d;
    }
    if(count_d == (grid.size() -1)){
        if(player_in_turn(player_turn + 1) == "X"){
            std::cout << "Cross won diagonally"<< std::endl;
         }
         else{
            std::cout << "Nought won diagonally"<< std::endl;
         }
         std::cout << "Game over!" << std::endl;
         return true;
    }
    return false;
}

// Funktio tarkastaa, tuleeko pelilauta täyteen
bool is_grid_full(std::vector< std::vector<char> >& grid, int turn){
    //Jos ei tule voittoa, eikä pelilautaa laajenneta, peli loppuu
    if(! check_for_winner(grid, turn)){
        for(size_t i = 0; i < grid.size(); ++i){
            for(size_t j = 0; j < grid.size(); ++j){
                if(grid.at(i).at(j) == '.'){
                    return false;
                }
            }
        }
        std::cout << "No empty places" << std::endl;
        std::cout << "Game over!" << std::endl;
        return true;
    }
    return true;
}

// Funktio lisää merkin pelilautaan pelaajan perusteella
void add_coordinates(std::string x, std::string y,
                     std::vector< std::vector<char> >& grid,
                     int player_turn){

    if(player_in_turn(player_turn) == "X"){
        // Jos pelilautaa laajennettiin ylöspäin ja vasemmalle
        if(stoi(x) == 0 || stoi(y) == 0){
            grid.at(stoi(y)).at(stoi(x)) = 'X';
        }
        else{
            grid.at(std::stoi(y) -1).at(std::stoi(x) - 1) = 'X';
        }
    }

    else{
        if(stoi(x) == 0 || stoi(y) == 0){
            grid.at(stoi(y)).at(stoi(x)) = '0';
        }
        else{
            grid.at(std::stoi(y) -1).at(std::stoi(x) - 1) = '0';
        }
    }
    print_grid(grid);
}

// Funktio kysyy ja lukee koordinaatit
void read_coordinates(std::vector< std::vector<char> >& grid){
    std::cout << "Start game:" << std::endl;
    print_grid(grid);

    int player_turn = 1;
    std::string x = "";
    std::string y = "";

    while(!is_grid_full(grid, player_turn)){
    while(true){
        std::cout << "For " << player_in_turn(player_turn) <<
                     ", enter coordinates: x y> ";
        std::cin >> x;

        // Tarkistetaan ensin, onko ensimmäinen syöte lopetuskomento
        if(x == "q"){
            std::cout << "Why on earth you are giving up the game?"
            << std::endl;
            return;
        }
        std::cin >> y;

        //Syötettä luetaan käyttäjältä kunnes se kelpaa
        if(check_input(x, y, grid)){
            break;
        }
    }
    add_coordinates(x, y, grid, player_turn);
    ++player_turn;
    }
}


int main()
{
    std::vector< std::vector<char> > grid = {};
    make_grid(grid, DEFAULT_SIZE);
    read_coordinates(grid);



    return 0;
}
