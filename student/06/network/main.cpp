#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>

using OrganizationMap = std::map< std::string, std::vector< std::string >>;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void store_command(OrganizationMap& underlings_by_name,
                   const std::string& boss_id,
                   const std::string& underling_id){

    underlings_by_name.try_emplace({boss_id, {}});
    underlings_by_name.at(boss_id).push_back(underling_id);
    assert(underlings_by_name.count(underling_id) == 0);
    underlings_by_name[underling_id] = {};

}

void print_command(const OrganizationMap& underlings_by_name,
                   const std::string& boss_id,
                   unsigned current_depth = 0){

    std::cout << std::string(current_depth * 2, '.') << boss_id << std::endl;
    for(const auto& underling : underlings_by_name.at(boss_id)){
        print_command(underlings_by_name, underling, current_depth + 1);
    }
}

unsigned count_command(const OrganizationMap& underlings_by_name,
                       const std::string& boss_id){

    const auto& underlings = underlings_by_name.at(boss_id);
    unsigned underlings_count = underlings.size();

    for(const auto& underling : underlings){
        underlings_count += count_command(underlings_by_name, underling);
    }
    return underlings_count;
}

int main()
{
    OrganizationMap underlings_by_name;


    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store_command(underlings_by_name, id1, id2);

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print_command(underlings_by_name, id);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << count_command(underlings_by_name, id) << std::endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
