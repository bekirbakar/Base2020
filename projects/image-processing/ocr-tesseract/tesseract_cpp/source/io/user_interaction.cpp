#include <vector>
#include <string>
#include <iostream>

#include "io/user_interaction.h"

std::vector<std::string> readTesseractConfiguration()
{
    std::vector<std::string> output;
    std::string input;

    std::cout << "Enter path to tessdata." << std::endl;
    std::getline(std::cin, input);
    output.push_back(input);

    std::cout << "Enter prior language." << std::endl;
    std::getline(std::cin, input);
    output.push_back(input);

    std::cout << "Enter path to image for ocr." << std::endl;
    std::getline(std::cin, input);
    output.push_back(input);

    return output;
}
