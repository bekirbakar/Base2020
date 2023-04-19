#include <iostream>
#include <Windows.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "OCR/ocr.h"

std::string tesseractOcr(const char *tessDataFolder, const char *language,
                         const char *source)
{
    auto *baseApi = new tesseract::TessBaseAPI();

    if (baseApi->Init(tessDataFolder, language))
    {
        const auto *const errorMessage = "Could not initialize tesseract.\n";

        fprintf(stderr, errorMessage);

        return errorMessage;
    }

    auto *image = pixRead(source);
    baseApi->SetImage(image);
    baseApi->SetSourceResolution(70);

    const char *output = baseApi->GetUTF8Text();

    baseApi->End();

    pixDestroy(&image);
    delete baseApi;

    return output;
}

void tesseractPreprocess(const std::string &sourceFile)
{
    const bool performNegate = TRUE;
    const auto darkBgThreshold = 0.5f;

    const auto performScale = 1;

    const auto performUnSharpMask = 1;
    // const auto usmHalfWidth = 5;
    // const auto usmFract = 2.5f;

    const auto performOtsuBinarize = 1;
    // const auto otsuSx = 2000;
    // const auto otsuSy = 2000;
    // const auto otsuSmoothx = 0;
    // const auto otsuSmoothy = 0;
    // const auto otsuScoreFract = 0.0f;

    // char* ext = nullptr;

    auto *pixs = pixRead(sourceFile.c_str());

    pixs = pixConvertRGBToGray(pixs, 0.0f, 0.0f, 0.0f);

    if (performNegate)
    {
        PIX *otsuPixs = nullptr;

        auto borderAvg = pixAverageOnLine(otsuPixs, 0, 0, otsuPixs->w - 1,
                                          0, 1);

        borderAvg += pixAverageOnLine(otsuPixs, 0, otsuPixs->h - 1,
                                      otsuPixs->w - 1, otsuPixs->h - 1, 1);

        borderAvg += pixAverageOnLine(otsuPixs, 0, 0, 0,
                                      otsuPixs->h - 1, 1);
        borderAvg += pixAverageOnLine(otsuPixs, otsuPixs->w - 1, 0,
                                      otsuPixs->w - 1, otsuPixs->h - 1, 1);
        borderAvg /= 4.0f;

        pixDestroy(&otsuPixs);

        if (borderAvg > darkBgThreshold)
        {
            pixInvert(pixs, pixs);
        }
    }

    if (performScale == true)
    {
        // pixs = pixScaleGrayLI(pixs, scaleFactor, scaleFactor);
    }

    if (performUnSharpMask == true)
    {
        // pixs = pixUnsharpMaskingGray(pixs, usmHalfWidth, usmFract);
    }

    if (performOtsuBinarize == true)
    {
    }

    char tempPath[128] = "D:\\";
    GetTempPathA(128, tempPath);
    strcat_s(tempPath, "preprocess_ocr.bmp");

    char preprocessed_file[150];
    strcpy_s(preprocessed_file, tempPath);

    char preprocessedFile[100] = ("path-to-image");
    status = pixWriteImpliedFormat(preprocessed_file, pixs, 0, 0);
    string out(preprocessedFile);

    return out;
}
