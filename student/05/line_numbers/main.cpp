#include <iostream>
#include <fstream>


int main()
{
    std::string file = "";
    std::cout << "Input file: ";
    std::cin >> file;

    std::ifstream file_in(file);
    std::string output_file = file.substr(0, 1) + ".output";
    std::ofstream file_out(output_file);


    if(! file_in || ! file_out){
        std::cout << "Output file: "<< "a.output" << std::endl;
        std::cout << "Error! The file " << file << " cannot be opened."
        << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Output file: "<< output_file << std::endl;
    int row_number = 1;
    std::string row = "";

    while(getline(file_in, row)){

        file_out << row_number << " " << row << std::endl;

        ++row_number;
    }

    file_in.close();
    file_out.close();


    return EXIT_SUCCESS;
}
