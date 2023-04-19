#include <vector>
#include <string>
#include <fstream>
#include <tchar.h>
#include <iostream>
#include <fileapi.h>
#include <WinBase.h>

#include "main.h"
#include "io/user_interaction.h"

extern std::string tesseractPreprocess(const std::string &sourceFile);
extern std::string tesseractOcr(const std::string &preprocessedFile);

int main()
{
    const std::string sourceFile = R "(sample.jpeg)";

    const std::ifstream infile(sourceFile);
    if (!infile.good())
    {
        std::cout << "File not found!";
        return 1;
    }

    const auto preprocessedFile = tesseractPreprocess(sourceFile);

    const auto ocrResult = tesseractOcr(preprocessedFile);

    std::cout << ocrResult.c_str();

    return 1;
}
