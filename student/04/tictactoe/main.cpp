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
    if(grid.at(y1 - 1).at(x1 - 1) != '.'){
        std::cout << "The given place is already occupied" << std::endl;
        return false;
    }
    return true;
}

// Funktio käy läpi ja tarkastaa eri voittotilanteet
bool check_for_winner(std::vector< std::vector<char> >& grid, int player_turn){
    size_t count_crosses = 1; // Laskee vierekkäiset ristit
    size_t count_noughts = 1; // Laskee vierekkäiset nollat

    for(size_t i = 0; i < (grid.size() - 1); ++i){
        //Voitto rivillä
        for(size_t j = 0; j < (grid.size() - 1); ++j){
            if(grid.at(i).at(j) == grid.at(i).at(j+1) && grid.at(i).at(j) != '.'){
                if(grid.at(i).at(j) == 'X'){
                    count_crosses += 1;
                }
                else{
                    count_noughts += 1;
                }
            }
        }
        if(count_noughts == grid.size() || count_crosses == grid.size()){
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
        count_crosses = 1; count_noughts = 1;
        for(size_t k = 0; k < (grid.size() - 1); ++k){
            if(grid.at(k).at(i) == grid.at(k+1).at(i) && grid.at(k).at(i) != '.'){
                if(grid.at(k).at(i) == 'X'){
                    count_crosses += 1;
                }
                else{
                    count_noughts += 1;
                }
            }
        }
        if(count_noughts == grid.size() || count_crosses == grid.size()){
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
    count_crosses = 1; count_noughts = 1;
    for(size_t m = 0; m < (grid.size()-1); ++m){
        if(grid.at(m).at(m) == grid.at(m+1).at(m+1) && grid.at(m).at(m) != '.'){
            if(grid.at(m).at(m) == 'X'){
                 count_crosses += 1;
             }
             else{
                count_noughts += 1;
             }
            }
    }
    if(count_noughts == grid.size() || count_crosses == grid.size()){
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
    count_crosses = 1; count_noughts = 1;
    for(size_t m = 0; m < (grid.size()-1); ++m){
        for(size_t n = (grid.size()-1); n > 0; --n){
            if(grid.at(n).at(m) == grid.at(n-1).at(m+1) && grid.at(n).at(m) != '.'){
                if(grid.at(n).at(m) == 'X'){
                     count_crosses += 1;
                 }
                 else{
                    count_noughts += 1;
                 }
                }
            }
        if(count_noughts == grid.size() || count_crosses == grid.size()){
            if(player_in_turn(player_turn + 1) == "X"){
                std::cout << "Cross won diagonally"<< std::endl;
             }
             else{
                std::cout << "Nought won diagonally"<< std::endl;
             }
             std::cout << "Game over!" << std::endl;
             return true;
        }
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


// Funktio lisää merkin tauluun pelaajan perusteella
void add_coordinates(std::string x, std::string y,
                     std::vector< std::vector<char> >& grid,
                     int player_turn){
    if(player_in_turn(player_turn) == "X"){
        grid.at(std::stoi(y) -1).at(std::stoi(x) - 1) = 'X';
    }
    else{
        grid.at(std::stoi(y) - 1).at(std::stoi(x) - 1) = '0';
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
