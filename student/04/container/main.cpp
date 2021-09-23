#include <cstdlib>
#include <iostream>
#include <vector>

#include <string>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(std::vector<int>& integers){
    // Checks are all of the integers the same

    int first_integer = integers.front();

    for(int integer : integers){
        if(integer != first_integer){
            return false;
        }
    }

    return true;
}


bool is_ordered_non_strict_ascending(std::vector<int>& integers){
    // Are integers in non strict ascending order

    size_t i = 1;
    while(i < integers.size()){
        if(integers.at(i) < integers.at(i - 1)){
            return false;
        }
        ++i;
    }
    return true;
}

bool is_arithmetic_series(std::vector<int>& integers){
    int difference = integers.at(1) - integers.at(0);  //Assumed that size is larger than one
    size_t i = 1;
    while(i < integers.size()){
        if((integers.at(i) - integers.at(i - 1)) != difference){
            return false;
        }
        ++i;
    }
    return true;

}

bool is_geometric_series(std::vector<int>& integers){
    return true;
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
