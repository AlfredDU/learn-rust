#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

const std::string TEXTFILE = "res/GNU通用公共许可协议3.0.txt";

int main(int argc, char* argv[])
{
    std::ifstream reader(TEXTFILE);
    std::stringstream source;

    if (reader.is_open()) {
        source << reader.rdbuf();
        reader.close();
    } else {
        std::cerr << "Unable to read file: " + TEXTFILE << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << source.str() << std::endl;
    

    return EXIT_SUCCESS;
}