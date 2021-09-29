#include <iostream>
#include <fstream>

int main()
{
    std::string file_name = "";
    std::cout <<"Input file: ";
    getline(std::cin, file_name);

    std::string output_file = "a.output";
    std::cout << "Output file: " << output_file << std::endl;

    std::ifstream file(file_name);
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

        ++row_number;
    }

    file.close();
    newfile.close();



    return EXIT_SUCCESS;
}
