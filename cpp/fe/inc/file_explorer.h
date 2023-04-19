#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <string>
#include <filesystem>

class FileExplorer
{
public:
    explicit FileExplorer(const std::string& message);
    //~FileExplorer();

    std::string absolutePath;
    std::string extension;
    std::filesystem::file_time_type modifiedAt;
    int processedAt;
    int fileSize;
    bool status;
    bool isDeleted;
    bool pushed;
    const std::string message;

    bool scanFiles(const std::string& pathToExplore);
    bool isFileSupported(std::string& keyword) const;
};

#endif // !FILE_EXPLORER_H