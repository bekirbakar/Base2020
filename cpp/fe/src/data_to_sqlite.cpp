#include <string>
#include <iostream>
#include <sqlite3.h>
#include <list>
#include <string>
#include <iostream>
#include <filesystem>
#include <SQLiteCpp/SQLiteCpp.h>

int callback(void *data, int argc, char **argv, char **azColName)
{
    fprintf(stderr, "%s: ", static_cast<const char *>(data));

    for (auto i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    return 0;
}

int run()
{
    // Open database.
    sqlite3 *db;
    auto exit = sqlite3_open("example.db", &db);

    if (exit)
    {
        std::cerr << "Error: " << sqlite3_errmsg(db) << std::endl;
        return (-1);
    }

    std::cout << "Opened database successfully!" << std::endl;

    // Create table.
    const std::string sql("create table if not exists person (name text"
                          "not null, surname text not null," 
                          "primary key(name));");
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &messageError);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error creating table! " << std::endl;
        sqlite3_free(messageError);
    }

    std::cout << "Table created successfully!" << std::endl;

    // Run query.
    std::string query(R "(insert into person values(" bekir ", " bakar "))");

    sqlite3_exec(db, query.c_str(), callback, nullptr, nullptr);
    query = R "(insert into person values(" bekir ", " bakar "))";
    sqlite3_exec(db, query.c_str(), callback, nullptr, nullptr);

    query = R "(delete from person where name " jack ")";
    exit = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &messageError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error DELETE" << std::endl;
        sqlite3_free(messageError);
    }

    std::cout << "Record deleted successfully!" << std::endl;
    sqlite3_exec(db, query.c_str(), callback, nullptr, nullptr);

    // Close database.
    sqlite3_close(db);

    return 0;
}

void fileDataToDB(const auto root)
{
    std::list<std::string> buffer;

    for (const auto &entry : std::filesystem::directory_iterator(root))
    {
        auto absolutePath = entry.path().string();
        auto extension = entry.path().extension().string();
        auto modifiedAt = Fs::last_write_time(absolutePath);
        auto = 1234;
        auto size = Fs::file_size(absolutePath);
        auto status = false;
        auto isDeleted = false;
        auto pushed = false;

        std::cout << absolutePath << std::endl;

        if (entry.is_directory())
        {
            std::cout << "Directory:  " << absolutePath << '\n';
        }
        else if (entry.is_regular_file())
        {
            std::cout << "File: " << absolutePath << '\n';
        }
        else
        {
            std::cout << "Unknown type detected! " << absolutePath << '\n';
        }

        std::ostringstream sql;
        sql << "INSERT INTO FILES " << status << "," << status << ",";
        buffer.push_front(sql.str());
        std::cout << sql.str() << std::endl;
    }
}