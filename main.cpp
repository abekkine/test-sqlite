#include <sqlite3.h>

#include <stdexcept>
#include <iostream>
#include <chrono>
#include <thread>

static int callback(void * data, int argc, char **argv, char** azColName) {
    // TODO : Handle query result...
    for (int i=0; i<argc; ++i) {
        std::cout << std::string(azColName[i]) << " > " << std::string(argv[i]) << ", ";
    }
    std::cout << '\n';
    // if (data != nullptr) {
    //     std::cout << "query-id(" << ((int *)data)[0] << ")\n";
    // }
    return 0;
}

int main(int argc, char** argv) {
    int exitCode = 2;
    int retval;
    sqlite3 * db_handle;
    char * error_message = 0;

    try {
        // Initialize database
        retval = sqlite3_open("test.db", &db_handle);
        if (retval != SQLITE_OK) {
            throw std::runtime_error("Unable to open test.db!");
        }

        retval = sqlite3_exec(db_handle
            , "create table 'test_table' ('id' integer, 'value' integer);"
            , callback
            , 0
            , &error_message
        );
        if (retval != SQLITE_OK) {
            std::cerr << "Unable to create table!\n";
        }

        int query_id = 100;
        retval = sqlite3_exec(db_handle
            , "select * from 'test_table';"
            , callback
            , (void *)&query_id
            , &error_message
        );
        if (retval != SQLITE_OK) {
            throw std::runtime_error("Unable to execute select query!");
        }

        sqlite3_close(db_handle);

        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        exitCode = 0;
    }
    catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
    }


    return exitCode;
}