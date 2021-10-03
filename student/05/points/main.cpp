#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

int main()
{
    std::string file = "";
    std::cout << "Input file: ";
    std::cin >> file;

    std::ifstream file_in(file);

    if(! file_in){
        std::cout << "Error! The file " << file << " cannot be opened."
        << std::endl;
        return EXIT_FAILURE;
    }

    std::map< std::string, int> player_scores;
    std::string line;
    size_t sep;
    std::string name = "";
    int score = 0;

    while(getline(file_in, line)){
        sep = line.find(':');
        name = line.substr(0, sep);
        score = stoi(line.substr(sep+1, line.length() - (sep + 1)));

        //Jos nimeä ei ole vielä mapissa
        if(player_scores.find(name) == player_scores.end()){
            player_scores.insert({name, score});
        }
        else{
            player_scores.at(name) += score;
        }

    }

    for(auto& pair: player_scores){
        std::cout<< pair.first << ": " << pair.second << std::endl;
    }



    return EXIT_SUCCESS;
}
