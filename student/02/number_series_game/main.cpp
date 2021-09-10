#include <iostream>


int main()
{
    int numbers = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> numbers;
    for (int number = 1; number <= numbers; ++number){
        std::cout << number << std::endl;
    }
}
