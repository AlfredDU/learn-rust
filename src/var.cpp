/*
 * This program needs boost library.
 */
#include <boost/any.hpp>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

namespace sheet {
    
    typedef boost::any cell;
    typedef std::map<std::string, cell> row;
    
    int INTEGER = 0;
    float REAL = 0.0;
    std::string TEXT = "";
    
    class Sheet {
        
    public:
        Sheet(row schema) {
            
            if (schema.empty()) {
                std::cerr << "empty schema" << std::endl;
                exit(EXIT_FAILURE);
            }
            
            for (auto iter = schema.begin(); iter != schema.end(); iter++) {
                
                if ( (iter->second).type() == typeid(int) ) {
                    if ( ! (boost::any_cast<int>(iter->second) == INTEGER) ) {
                        exit(EXIT_FAILURE);
                    }
                } else if ( (iter->second).type() == typeid(float) ) {
                    if ( ! (boost::any_cast<float>(iter->second) == REAL) ) {
                        exit(EXIT_FAILURE);
                    }
                } else if ( (iter->second).type() == typeid(double) ) {
                    if ( ! (boost::any_cast<double>(iter->second) == static_cast<double>(REAL)) ) {
                        exit(EXIT_FAILURE);
                    }
                } else if ( (iter->second).type() == typeid(std::string) ) {
                    if ( ! (boost::any_cast<std::string>(iter->second) == TEXT) ) {
                        exit(EXIT_FAILURE);
                    }
                } else {
                    exit(EXIT_FAILURE);
                }
            }
            
            this->schema = schema;
        };
        
        ~ Sheet(){};
        
    public:
        std::vector<row> rows;
        
    private:
        row schema;
        
    public:
        std::string getSchema() const {
            
            std::string schema_json = "{";
            std::map<std::string, cell>::size_type checkLast = 0;
            
            for (auto iter = (this->schema).begin(); iter != (this->schema).end(); iter++) {
                schema_json += ("{ " + iter->first + ": ");
                
                if ( (iter->second).type() == typeid(int) ) {
                    schema_json += "INTEGER }";
                } else if ( (iter->second).type() == typeid(float) ) {
                    schema_json += "REAL }";
                } else if ( (iter->second).type() == typeid(std::string) ) {
                    schema_json += "TEXT }";
                }
                
                if (checkLast + 1 != (this->schema).size()) {
                    schema_json += ", ";
                }
                
                checkLast ++;
            }
            
            schema_json += "}";
            return schema_json;
        };
        
        void insert(row newRow) {
            
            for (auto iter_x = newRow.begin(); iter_x != newRow.end(); iter_x++) {
                
                auto iter_i = (this->schema).begin();
                while (iter_i != (this->schema).end()) {
                    
                    if (iter_i->first == iter_x->first) {
                        break;
                    }
                    iter_i ++;
                }
                
                if (iter_i == (this->schema).end()) {
                    std::cerr << "unknown field: " << iter_x->first << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            
            for (auto iter = newRow.begin(); iter != newRow.end(); iter++) {
                if ((iter->second).type() != (((this->schema).find(iter->first))->second).type()) {
                    
                    std::cerr << "wrong type of field: " << iter->first << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            
            (this->rows).push_back(newRow);
        };
        
        template<class T>
        T at(int index, std::string field, T TYPE_MACRO) const {
            row iRow = (this->rows)[index];
            cell theCell = (iRow.find(field))->second;
            
            return boost::any_cast<T>(theCell);
        };
    };
}


int main(int argc, char* argv[])
{
    sheet::row avenger_schema = {
        {"name", sheet::TEXT},
        {"aka", sheet::TEXT},
        {"gender", sheet::INTEGER},
        {"actor", sheet::TEXT}
    };
    
    sheet::Sheet avengers(avenger_schema);
    
    sheet::row Black_Widow = {
        {"name", std::string{"Natasha Romanoff"} }, // Note: a value that assigned to boost::any must be specified with explicit type, especially std::string for characters enclosed in quote marks can be of various types.
        {"aka", std::string{"Black Widow"} },
        {"gender", 0},
        {"actor", std::string{"Scarlett Johnson"} }
    };
    avengers.insert(Black_Widow);
    
    std::cout << avengers.getSchema() << std::endl;
    std::cout << avengers.at(0, "name", sheet::TEXT) << std::endl;
    std::cout << avengers.at(0, "gender", sheet::INTEGER) << std::endl;
    
    return EXIT_SUCCESS;
}