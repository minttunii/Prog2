#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

int main(){

    std::string filepath = "";
    std::cout << "Input file: ";
    std::cin >> filepath;

    std::ifstream file_in(filepath);
    if(!file_in){
        std::cout << "Error! The file " << filepath <<" cannot be opened."
        << std::endl;
        return EXIT_FAILURE;
    }

    std::map< std::string, std::set< unsigned >> linenumbers_by_word;

    std::string line = "";
    unsigned linenro = 1;

    while (std::getline(file_in, line)) {
        std::string word;

        std::istringstream line_in(line);
        while (line_in >> word) {
            linenumbers_by_word.try_emplace({word, {} });
            linenumbers_by_word.at(word).insert(linenro);
        }
        ++linenro;
    }

    for(const std::pair<const std::string, std::set<unsigned>>& pair : linenumbers_by_word){
        const std::string& word = pair.first;
        const std::set<unsigned>& linenumbers =  pair.second;

        std::cout<< word << " " << linenumbers.size() << ": ";
        const auto last_item_it = --linenumbers.cend();
        for(auto it = linenumbers.cbegin(); it != linenumbers.cend(); ++it){
            std::cout<< *it;
            if(it != last_item_it){
                std::cout<< ", ";
            }
        }
        std::cout<<std::endl;
    }

    return EXIT_SUCCESS;
}
