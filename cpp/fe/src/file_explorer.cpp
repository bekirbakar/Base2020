#include <string>
#include <iostream>
#include <fileapi.h>
#include <algorithm>
#include <filesystem>
#include <timezoneapi.h>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "explorer.h"

#if defined(_WIN32)
#include <sys/stat.h>
#include <stringapiset.h>
#endif

std::time_t getFileWriteTime(const std::filesystem::path &filename)
{
#if defined(_WIN32)
    {
        struct _stat64 fileInfo
        {
        };
        if (_wstati64(filename.wstring().c_str(), &fileInfo) != 0)
        {
            throw std::runtime_error("Failed to get last write time.");
        }
        return fileInfo.st_mtime;
    }
#else
    {
        auto fsTime = std::filesystem::last_write_time(filename);
        return decltype(fsTime)::clock::to_time_t(fsTime);
    }
#endif
}

std::wstring s2Ws(const std::string &s)
{
    const auto sLength = static_cast<int>(s.length()) + 1;
    const auto len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength,
                                         nullptr, 0);
    auto *const buf = new wchar_t[len];

    MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength, buf, len);

    std::wstring r(buf);
    delete[] buf;

    return r;
}

FileExplorer::FileExplorer(
    const std::string &message) : processedAt(0), fileSize(0), status(false), isDeleted(false),
                                  pushed(false)
{
    std::cout << message << std::endl;
}

// FileExplorer::~FileExplorer() = default;

bool FileExplorer::isFileSupported(std::string &keyword) const
{
    const auto *const projectPath = R "(.\Config)";

    std::vector<std::string> supportedFileFormats;

    const std::filesystem::path dir(projectPath);
    const std::filesystem::path file("system.ini");
    const auto configPath = dir / file;

    boost::property_tree::ptree pt;
    read_ini(configPath.string(), pt);

    auto str1 = pt.get<std::string>("deprecated.supported_extensions");

    typedef std::vector<boost::iterator_range<std::string::iterator> >
        FindVectorType;

    FindVectorType findVec;

    ifind_all(findVec, str1, "abc");

    typedef std::vector<std::string> SplitVectorType;

    SplitVectorType splitVec;

    boost::split(splitVec, str1, boost::is_any_of(","),
                 boost::token_compress_on);

    if (std::find(splitVec.begin(),
                  splitVec.end(), keyword) != splitVec.end())
    {
        return true;
    }

    return false;
}

bool FileExplorer::scanFiles(const std::string &pathToExplore)
{
    using namespace std;
    using namespace boost;

    std::filesystem::recursive_directory_iterator entry(pathToExplore);
    const std::filesystem::recursive_directory_iterator end;

    while (entry != end)
    {
        // Get current path string.
        absolutePath = entry->path().string();

        // Get last write time.
        // const auto modifiedAt = getFileWriteTime(absolutePath);
        // const auto modifiedAtTime = asctime(localtime(&modifiedAt));
        // cout << modifiedAtTime << endl;

        // Get system time.
        // auto start = chrono::system_clock::now();
        // auto now = chrono::system_clock::to_time_t(start);
        // std::cout << ctime(&now) << endl;

        if (entry->is_directory())
        {
            if (entry->path().filename().string() == "java")
            {
                std::filesystem::recursive_directory_iterator(entry)
                .disable_recursion_pending();

                error_code ec;

                if (ec)
                {
                    std::cerr << "Error: " << entry->path().string()
                    << " :: " << ec.message() << endl;
                }
            }
            else
            {
                cout << "Directory: " << absolutePath << endl;
            }
        }
        else if (entry->is_regular_file())
        {
            extension = entry->path().extension().string();

            // auto size = entry->file_size();
            // auto status = false;
            // auto isDeleted = false;
            // auto pushed = false;

            if (isFileSupported(extension))
            {
                cout << "File: " << absolutePath << endl;
            }
            else
            {
                cout << "File not supported!" << endl;
            }
        }
        else
        {
            cout << "Neither file nor directory! " << absolutePath << endl;
        }

        ++entry;

        // Insert to database.

        //  std::ostringstream sql;
        //  sql << "INSERT INTO FILES " << status << "," << status << ",";
        //  buffer.push_front(sql.str());
        //  std::cout << sql.str() << std::endl;
    }

    return true;
}

bool isSkipList()
{
    const std::vector<std::string> skipList = {};
    std::vector<std::string> items = {};

    // find(skipList.begin(), skipList.end(), iter->path().filename())
    // != dirSkipList.end();
    // listOfFiles.push_back(iter->path().string());

    return true;
}

std::vector<std::string> getPhysicalDrives()
{
    std::vector<std::string> drives;

    WCHAR szLogicalDrives[MAX_PATH] = {0};
    const DWORD dwSize = MAX_PATH;

    const auto dwResult = GetLogicalDriveStrings(dwSize, szLogicalDrives);

    if (dwResult > 0 && dwResult <= MAX_PATH)
    {
        auto *szSingleDrive = szLogicalDrives;
        while (*szSingleDrive)
        {
            // auto nDriveType = GetDriveType(szSingleDrive);

            const auto sizeNeeded = WideCharToMultiByte(
                CP_UTF8, 0, static_cast<LPCWCH>(szSingleDrive), -1, nullptr,
                0, nullptr, nullptr);
            auto *const stringMe = new char[sizeNeeded + 1];

            WideCharToMultiByte(CP_UTF8, 0,
                                static_cast<LPCWCH>(szSingleDrive),
                                -1, stringMe, sizeNeeded,
                                nullptr, nullptr);
            // stringMe[sizeNeeded + 1] = NULL; // Add +1 ----- +1

            // get the next drive
            szSingleDrive += wcslen(szSingleDrive) + 1;

            drives.emplace_back(stringMe);
        }

        for (const auto &s : drives)
        {
            auto stem = s2Ws(s);
            const auto *const result = stem.c_str();

            const auto res = GetDriveType(result); // this is device type
            // extract removable one

            // switch to valid ones

            std::cout << s << std::endl;
            std::cout << res << std::endl;
        }
    }

    return drives;
}

bool scanDirectory(const std::string &head)
{
    std::list<std::tuple<std::string, std::string, int, int, bool, bool,
                         bool> >
        fileProperties;

    for (const auto &entry :
         std::filesystem::recursive_directory_iterator(head))
    {
        std::string absolutePath;
        std::string extension;
        std::filesystem::file_time_type modifiedAt;
        int processedAt;
        uintmax_t size;
        bool status;
        bool isDeleted;
        bool pushed;

        std::tuple<std::string, std::string, int, int, bool, bool, bool>
            current = {absolutePath, extension, processedAt, size, status,
                       isDeleted, pushed};

        fileProperties.push_front(make_tuple(absolutePath, extension,
                                             processedAt, size, status,
                                             isDeleted, pushed));

        if (entry.is_directory())
        {
            std::cout << "Directory: " << absolutePath << "\n\n\n";

            absolutePath = entry.path().string();
            extension = entry.path().extension().string();
            modifiedAt = std::filesystem::last_write_time(absolutePath);

            SYSTEMTIME st_system_time;
            if (
                FileTimeToSystemTime(
                    reinterpret_cast<const FILETIME *>(&modifiedAt),
                    &st_system_time))
            {
                printf("Year = %d,  Month = %d,  Day = %d,  Hour = %d,"
                       "  Minute = %d\n",
                       st_system_time.wYear, st_system_time.wMonth,
                       st_system_time.wDay, st_system_time.wHour,
                       st_system_time.wMinute);
            }

            processedAt = 1234;
            size = std::filesystem::file_size(absolutePath);
            status = false;
            isDeleted = false;
            pushed = false;
        }
        else if (entry.is_regular_file())
        {
            absolutePath = entry.path().string();
            extension = entry.path().extension().string();
            modifiedAt = std::filesystem::last_write_time(absolutePath);

            SYSTEMTIME stSystemTime;
            if (FileTimeToSystemTime(
                    reinterpret_cast<const FILETIME *>(&modifiedAt),
                    &stSystemTime))
            {
                printf("Year = %d,  Month = %d,  Day = %d,  Hour = %d,"
                       "  Minute = %d\n",
                       stSystemTime.wYear, stSystemTime.wMonth,
                       stSystemTime.wDay, stSystemTime.wHour,
                       stSystemTime.wMinute);
            }

            processedAt = 1234;
            size = std::filesystem::file_size(absolutePath);
            status = false;
            isDeleted = false;
            pushed = false;

            std::cout << "File: " << absolutePath << '\n';
        }
        else
        {
            std::cout << "Unknown type detected! " << absolutePath
                      << "\n\n\n";
        }
    }

    return true;
}

std::vector<std::string> getAllFilesInDir(
    const std::string &dirPath,
    const std::vector<std::string> &dirSkipList = {})
{
    std::vector<std::string> listOfFiles;
    try
    {
        // Check if given path exists and points to a directory.
        if (std::filesystem::exists(dirPath) &&
            std::filesystem::is_directory(dirPath))
        {
            std::filesystem::recursive_directory_iterator iter(dirPath);
            const std::filesystem::recursive_directory_iterator end;

            while (iter != end)
            {
                // Check if current entry is a directory and if exists in
                // skip list.
                if (
                    is_directory(iter->path()) &&
                    (std::find(dirSkipList.begin(),
                               dirSkipList.end(),
                               iter->path().filename()) != dirSkipList.end()))
                {
                    iter.disable_recursion_pending();
                }
                else
                {
                    // Add the name in vector
                    listOfFiles.push_back(iter->path().string());
                }

                std::error_code ec;
                // Increment the iterator to point to next entry in recursive
                // iteration.
                iter.increment(ec);
                if (ec)
                {
                    std::cerr << "Error While Accessing : " <<
                    iter->path().string() << " :: " << ec.message() << '\n';
                }
            }
        }
    }
    catch (std::system_error &e)
    {
        std::cerr << "Exception :: " << e.what();
    }
    return listOfFiles;
}

// USE

// auto val = isFileSupported(".png");

// if (val == true)
//     cout << "Supported" << endl;
// else
//     cout << "Not supported" << endl;

// cout << "Exit point." << endl;

// vector<string> supportedFileFormats = {".png", ".jpg"};

// for (const auto& s : supportedFileFormats)
// {
//     val = isFileSupported(s);

//     if (val == true)
//         cout << "Supported" << endl;
//     else
//         cout << "Not supported" << endl;
// }

// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-
// getdrivetypea?redirectedfrom=MSDN
