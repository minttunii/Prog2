#include <iostream>
#include <fstream>

int main()
{
    std::string name = "";
    std::string input_file = "";
    std::cout <<"Input file: ";
    getline(std::cin, name, '.');
    input_file = name + ".input";


    std::string output_file = name + ".output";
    std::cout << "Output file: " << output_file << std::endl;

    std::ifstream file(input_file);
    if(not file){
        std::cout <<"Error! The file not_a_file.input cannot be opened."
        << std::endl;
        return EXIT_FAILURE;
    }

    int row_number = 1;
    std:: string row = "";
    std::ofstream newfile(output_file);
    while(getline(file, row)){

        newfile <<row_number <<" "<< row << std::endl;
        newfile << std::endl;

        ++row_number;
    }

    file.close();
    newfile.close();



    return EXIT_SUCCESS;
}
