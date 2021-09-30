#include <iostream>
#include <fstream>

int main()
{
    std::string name = "";
    std::string input_file = "";
    std::string output_file = "";
    std::cout <<"Input file: ";
    getline(std::cin, input_file);
    name = input_file.at(0);

    std::ifstream file(input_file);
    if(not file){
        std::cout << "Output file: " << "a.output" << std::endl;
        std::cout <<"Error! The file " << input_file << " cannot be opened."
        << std::endl;
        return EXIT_FAILURE;
    }
    else{
        output_file = name + ".output";
        std::cout << "Output file: " << output_file << std::endl;
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
