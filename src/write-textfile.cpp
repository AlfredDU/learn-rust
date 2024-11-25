/*
 * This program needs C++11 support.
 */
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

const std::string PLAINTEXT_FILE = "res/Tagore.txt";
const std::string ENCRYPTED_FILE = "res/Encrypted.txt";

const std::map<char, std::string> Morse = {
    {'A',	".-"},
    {'B',	"-..."},
    {'C',	"-.-."},
    {'D',	"-.."},
    {'E',	"."},
    {'F',	"..-."},
    {'G',	"--."},
    {'H',	"...."},
    {'I',	".."},
    {'J',	".---"},
    {'K',	"-.-"},
    {'L',	".-.."},
    {'M',	"--"},
    {'N',	"-."},
    {'O',	"---"},
    {'P',	".--."},
    {'Q',	"--.-"},
    {'R',	".-."},
    {'S',	"..."},
    {'T',	"-"},
    {'U',	"..-"},
    {'V',	"...-"},
    {'W',	".--"},
    {'X',	"-..-"},
    {'Y',	"-.--"},
    {'Z',	"--.."},
    {'0',	"-----"},
    {'1',	".----"},
    {'2',	"..---"},
    {'3',	"...--"},
    {'4',	"....-"},
    {'5',	"....."},
    {'6',	"-...."},
    {'7',	"--..."},
    {'8',	"---.."},
    {'9',	"----."},
    {'.',	".-.-.-"},
    {',',	"--..--"},
    {':',	"---..."},
    {'?',	"..--.."},
    {'\'',	".----."},
    {'-',	"-....-"},
    {'\"',	".-..-."},
    {' ',   "  "},
    {'\n',  ".-.-"}
};


int main(int argc, char* argv[])
{
    std::ifstream reader( PLAINTEXT_FILE );
    std::string buffer;
    std::vector<std::string> plainText;
    
    if (reader.is_open()) {
        while (getline(reader, buffer)) {
            plainText.push_back(buffer);
        }
        reader.close();
    } else {
        std::cerr << "Input error.";
        return EXIT_FAILURE;
    }
    
    std::vector<std::string> encryptedText;
    
    for (auto line : plainText) {
        buffer = "";
        for (char c : line) {
            auto iter = Morse.find(toupper(c));
            if (iter != Morse.end()) {
                buffer += iter->second;
            }
            buffer += ' ';
        }
        buffer += Morse.find('\n')->second;
        buffer += ' ';
        
        encryptedText.push_back(buffer);
    }
    
    std::ofstream writer( ENCRYPTED_FILE );
    if (writer.is_open()) {
        for (auto iter = encryptedText.begin(); iter != encryptedText.end(); iter ++) {
            writer << *iter;
        }
        writer.close();
    } else {
        std::cerr << "Output error.";
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}