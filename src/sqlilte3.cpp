/*
 * This program needs extra library linking.
 */
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <cstdlib>


const std::string dbname = "res/avengers.db";


class Sqlite3 {
    /* Simple C++ wrapper for sqlite3 c interface. */
public:
    Sqlite3() {};
    ~Sqlite3() {};
    
private:
    sqlite3* db;
    int* affectedRows = nullptr;

public:
    void open(const std::string dbfile) {
        int return_code = sqlite3_open(dbfile.c_str(), &(this->db));
        if (return_code != SQLITE_OK) {
            std::cout << sqlite3_errmsg(this->db);
            exit(EXIT_FAILURE);
        }
    };
    
    void close(void) {
        int return_code = sqlite3_close(this->db);
        if (return_code != SQLITE_OK) {
            std::cout << sqlite3_errmsg(this->db);
            exit(EXIT_FAILURE);
        }
    };
    
    void exec_ddl(std::string sql) {
        char* errmsg = nullptr;
        int return_code = sqlite3_exec(
                                       this->db,
                                       sql.c_str(),
                                       nullptr,      // Need not callback
                                       nullptr,      // Nothing to transfer to callback
                                       &errmsg
                                       );
        
        if (return_code != SQLITE_OK) {
            std::cout << errmsg;
            sqlite3_free(errmsg);
            exit(EXIT_FAILURE);
        }
    };
    
    static int callback(void* data, int cols, char** values, char** headers){
        std::string json_output = "[";
        
        for (int i = 0; i < cols; i++) {
            json_output += *headers;
            json_output += ": ";
            json_output += *values;
            
            if (i < cols - 1) {
                json_output += ", ";
            }
            headers ++;
            values ++;
        }
        json_output += "]";
        
        int* _affectedRows = static_cast<int*>(data);
        (*_affectedRows) ++; // Operator "++" precedes "*".
        
        std::cout << json_output << std::endl;
        
        return SQLITE_OK;
    };
    
    int exec_dml(std::string sql) {
        this->affectedRows = new int(0);
        
        char* errmsg = nullptr;
        int return_code = sqlite3_exec(
                                       this->db,
                                       sql.c_str(),
                                       Sqlite3::callback,    // Callback
                                       this->affectedRows,
                                       &errmsg
                                       );
        
        if (return_code != SQLITE_OK) {
            std::cout << errmsg;
            sqlite3_free(errmsg);
            exit(EXIT_FAILURE);
        }
        
        int _affectedRows = *(this->affectedRows);
        this->affectedRows = nullptr;
        return _affectedRows;
        };
    
} avengers;


int main(int argc, char* argv[])
{
    avengers.open(dbname);
    
    std::string sql_create_table_members =
        "CREATE TABLE IF NOT EXISTS members ("
            "id    INT    PRIMARY KEY    NOT NULL, "
            "name  TEXT                  NOT NULL, "
            "aka   TEXT"
        ")";
    avengers.exec_ddl(sql_create_table_members);
    
    int affectedRows;
    
    std::string sql_select_ironman =
        "SELECT * FROM members WHERE upper(aka) = \'IRON MAN\'";
    affectedRows = avengers.exec_dml(sql_select_ironman);
    
    if (affectedRows == 0) {
        std::string sql_insert_ironman =
            "INSERT INTO members "
            "(id, name, aka) "
            "VALUES "
            "(0, \'Tony Stark\',  \'Iron Man\')";
        avengers.exec_dml(sql_insert_ironman);
    }
    
    std::string sql_select_hawkeye =
        "SELECT * FROM members WHERE upper(aka) = \'HAWKEYE\'";
    affectedRows = avengers.exec_dml(sql_select_hawkeye);
    
    if (affectedRows == 0) {
        std::string sql_insert_hawkeye =
            "INSERT INTO members "
            "(id, name, aka) "
            "VALUES "
            "(1, \'Clint Barton\',  \'Hawkeye\')";
        avengers.exec_dml(sql_insert_hawkeye);
    }
    
    std::string sql_select_all_members = "SELECT * FROM members";
    avengers.exec_dml(sql_select_all_members);
    
    avengers.close();
    
    return EXIT_SUCCESS;
}