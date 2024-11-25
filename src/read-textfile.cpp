#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

const std::string TEXTFILE = "res/GNU通用公共许可协议3.0.txt";

int main(int argc, char* argv[])
{
    std::ifstream reader( TEXTFILE );
    std::string linebuffer;
    int ln = 0;
    
    if (reader.is_open()) {
        while (getline(reader, linebuffer)) {
            std::cout << linebuffer << std::endl; // Note: end-line mark '\n' is not included
            ln ++;
        }
        reader.close();
    } else {
        std::cout << "Unable to read this file: " + TEXTFILE << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Totally " << ln << " lines." << std::endl;
    
    return EXIT_SUCCESS;
}