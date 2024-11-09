#ifndef STRTOVECTOR_CONVERTER_H
#define STRTOVECTOR_CONVERTER_H

#include <vector>
#include <DMD32.h>

std::vector<std::vector<int>> stringToLEDGrid(const char* bChars, byte length, int left, int top, int totalRows);
std::vector<std::vector<int>> generateFlexibleGrid(const char* text, int length, int left, int top, int totalRows);

class VirtualDMD {
  private:
    std::vector<std::vector<bool>> grid;
    int width;
    int height;
    const uint8_t* Font;

    // Simple 5x7 font representation (same as before)
    static const uint8_t font[][5];

    unsigned char mapUTF8ToCustom(const char*& text);

  public:
    VirtualDMD(int displaysWide, int displaysHigh) : width(DMD_PIXELS_ACROSS * displaysWide), height(DMD_PIXELS_DOWN * displaysHigh)
    {
        grid.resize(height, std::vector<bool>(width, false));
    }

    void writePixel(unsigned int bX, unsigned int bY, byte bGraphicsMode, byte bPixel);

    void selectFont(const uint8_t* font);

    void drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode);

    int drawChar(int bX, int bY, const unsigned char letter, byte bGraphicsMode);

    int charWidth(const unsigned char letter);

    std::vector<std::vector<int>> getGrid() const;

    unsigned char mapTurkishChar(unsigned char c);

    static const uint8_t customWidths[];
    int getCustomWidth(unsigned char c);
    static const int CUSTOM_WIDTHS_SIZE = 96; // Total number of characters (including Turkish chars)
};

#endif