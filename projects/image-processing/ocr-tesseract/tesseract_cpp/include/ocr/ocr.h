#ifndef OCR_H
#define OCR_H

#include <string>
#include <iostream>

std::string tesseractOcr(const char *tessDataFolder, const char *language,
                         const char *source);

void tesseractPreprocess(const std::string &sourceFile);

#endif // !OCR_H
