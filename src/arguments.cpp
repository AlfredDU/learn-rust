#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

/*
 * Accept arguments with pattern like "cmd --param0 value0 --param1 value1".
 */

int main(int argc, char* argv[]) {
    
    std::map<std::string, std::string> arguments;
    
    if (argc % 2 == 0) {
        std::cerr << "improper arguments";
        return EXIT_FAILURE;
    }
    
    if (argc > 1) {
        
        for (int i = 1; i < argc - 1; i += 2) {
            std::string paramter_t(argv[i]);
            if (paramter_t.substr(0, 2) != "--"){
                std::cerr << "improper arguments";
                return EXIT_FAILURE;
            }
            
            std::string parameter = paramter_t.substr(2, paramter_t.length() - 2);
            std::string value(argv[i + 1]);
            
            arguments.insert(std::pair<std::string, std::string>(parameter, value)); //Alternatively: arguments[parameter] = value;
        }
    }
    
    std::cout << "{";
    std::size_t lastCheck = 0;
    for (auto iter = arguments.begin(); iter != arguments.end(); iter++) {
        lastCheck ++;
        std::cout << "\"" + iter->first + "\": \"" + iter->second + "\"";
        if (lastCheck != arguments.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "}";
    
    return EXIT_SUCCESS;
}