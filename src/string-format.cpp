/*
 * This program needs boost library.
 */
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <cstdlib>


struct player {
    std::string name;
    int age;
    std::string nation;
    std::string club;
    std::string position;
};

boost::format pattern( "%1%, aged %2%, is %3% %5% now serving %4%.");
player messi = {"Lionel Messi", 28, "Argentina", "FC Barcelona", "forward"};
player neymar = {"Neymar da Silva", 23, "Brazil", "FC Barcelona", "forward"};

std::string indefiniteArticle(std::string noun) {
    
    if (noun.empty()) {
        exit(EXIT_FAILURE);
    }
    
    char initial = boost::to_upper_copy(noun.substr(0, 1))[0];
    
    std::string article;
    switch (initial) {
        case 'A':
            article = "an ";
            break;
        case 'E':
            article = "an ";
            break;
        case 'I':
            article = "an ";
            break;
        case 'O':
            article = "an ";
            break;
        case 'U':
            article = "an ";
            break;
        default:
            article = "a ";
            break;
    }
    
    return article + noun;
};

std::string format(player p) {
    return (pattern % p.name % p.age % indefiniteArticle(p.nation) % p.club % p.position).str();
};


int main(int argc, char* argv[])
{
    
    std::cout << format(neymar) << std::endl;
    
    return EXIT_SUCCESS;
}