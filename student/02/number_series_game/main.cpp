#include <iostream>


int main()
{
    int numbers = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> numbers;
    for (int number = 1; number <= numbers; ++number){
        if (number % 7 == 0 and number % 3 == 0){
            std::cout << "zip boing" << std::endl;
        }
        else if (number % 7 == 0){
            std::cout << "boing" << std::endl;
        }
        else if (number % 3 == 0){
            std::cout << "zip" << std::endl;
        }
        else{
          std::cout << number << std::endl;
        }
    }
}
