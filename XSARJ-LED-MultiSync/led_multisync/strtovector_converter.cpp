
#include "strtovector_converter.hpp"
#include <DMD32.h>
#include "fonts/SystemFont5x7.h"

void VirtualDMD::writePixel(unsigned int bX, unsigned int bY, byte bGraphicsMode, byte bPixel)
{
    if (bX >= width || bY >= height) {
        return;
    }

    // Determine which panel the pixel belongs to
    int panel = bX / DMD_PIXELS_ACROSS;
    int xWithinPanel = bX % DMD_PIXELS_ACROSS;

    // Calculate the actual x-coordinate within the grid
    int actualX = panel * DMD_PIXELS_ACROSS + xWithinPanel;

    bool pixelState;
    switch (bGraphicsMode) {
    case GRAPHICS_NORMAL:
        pixelState = (bPixel == true); // true means pixel on
        break;
    case GRAPHICS_INVERSE: pixelState = (bPixel == false); break;
    case GRAPHICS_TOGGLE: pixelState = !grid[bY][actualX]; break;
    case GRAPHICS_OR: pixelState = grid[bY][actualX] | (bPixel == true); break;
    case GRAPHICS_NOR: pixelState = !(grid[bY][actualX] | (bPixel == true)); break;
    default: pixelState = (bPixel == true);
    }
    grid[bY][actualX] = pixelState;
}

// void VirtualDMD::drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode)
// {
//     if (bX >= width || bY >= height)
//         return;
//     uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
//     if (bY + height < 0)
//         return;

//     int strWidth = 0;
//     for (int i = 0; i < length; i++) {
//         int charWide = drawChar(bX + strWidth, bY, bChars[i], bGraphicsMode);
//         if (charWide > 0) {
//             strWidth += charWide + 1;
//         }
//         else if (charWide < 0) {
//             return;
//         }
//         if ((bX + strWidth) >= width || bY >= height)
//             return;
//     }
// }

// V2
// void VirtualDMD::drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode)
// {
//     if (bX >= width || bY >= height)
//         return;
//     uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
//     if (bY + height < 0)
//         return;

//     int strWidth = 0;
//     for (int i = 0; i < length; i++) {
//         int charWide = drawChar(bX + strWidth, bY, bChars[i], bGraphicsMode);
//         if (charWide > 0) {
//             // Only add extra spacing if it's not a small character like 'i'
//             // or if the next character isn't a small character
//             int extraSpace = 1;
//             if (charWide <= 2 || (i < length - 1 && charWidth(bChars[i + 1]) <= 2)) {
//                 extraSpace = 0; // No extra space for small characters
//             }
//             strWidth += charWide + extraSpace;
//         }
//         else if (charWide < 0) {
//             return;
//         }
//         if ((bX + strWidth) >= width || bY >= height)
//             return;
//     }
// }

// V3
// void VirtualDMD::drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode)
// {
//     if (bX >= width || bY >= height)
//         return;
//     uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
//     if (bY + height < 0)
//         return;

//     int strWidth = 0;
//     Serial.println("Character widths:");
//     for (int i = 0; i < length; i++) {
//         Serial.print("Character '");
//         Serial.print(bChars[i]);
//         Serial.print("': ");

//         // Get the width before drawing
//         int preWidth = charWidth(bChars[i]);
//         Serial.print("pre-width=");
//         Serial.print(preWidth);

//         // Draw and get the actual width used
//         int charWide = drawChar(bX + strWidth, bY, bChars[i], bGraphicsMode);
//         Serial.print(", actual-width=");
//         Serial.print(charWide);
//         Serial.print(", strWidth before=");
//         Serial.print(strWidth);

//         if (charWide > 0) {
//             strWidth += charWide + 1;
//             Serial.print(", strWidth after=");
//             Serial.println(strWidth);
//         }
//         else {
//             Serial.println(" (skipped)");
//             if (charWide < 0)
//                 return;
//         }

//         if ((bX + strWidth) >= width || bY >= height)
//             return;
//     }
// }

// 5
void VirtualDMD::drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode)
{
    if (bX >= width || bY >= height)
        return;
    uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
    if (bY + height < 0)
        return;

    int strWidth = 0;
    for (int i = 0; i < length; i++) {
        // Draw the character
        int charWide = drawChar(bX + strWidth, bY, bChars[i], bGraphicsMode);

        if (charWide > 0) {
            // Get the actual visual width for this character
            int visualWidth = getCustomWidth((unsigned char)bChars[i]);
            strWidth += visualWidth;

            // Add spacing between characters, but handle special cases
            if (i < length - 1) { // If not the last character
                unsigned char nextChar = bChars[i + 1];
                unsigned char currentChar = bChars[i];

                // Special case handling for specific character combinations
                if (currentChar == 'i' || currentChar == 'l' || currentChar == '.' || currentChar == '!' || currentChar == 'ı' ||
                    currentChar == 'İ') {
                    strWidth += 1; // Less space after narrow characters
                }
                else if (nextChar == 'i' || nextChar == 'l' || nextChar == '.' || nextChar == '!' || nextChar == 'ı' || nextChar == 'İ') {
                    strWidth += 1; // Less space before narrow characters
                }
                else {
                    strWidth += 2; // Normal spacing between characters
                }
            }
        }
        else if (charWide < 0) {
            return;
        }

        if ((bX + strWidth) >= width || bY >= height)
            return;
    }
}

// void VirtualDMD::drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode)
// {
//     if (bX >= width || bY >= height)
//         return;
//     uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
//     if (bY + height < 0)
//         return;

//     int strWidth = 0;
//     const char* ptr = bChars;
//     while (*ptr && (ptr - bChars) < length) {
//         unsigned char c = mapUTF8ToCustom(ptr);
//         int charWide = drawChar(bX + strWidth, bY, c, bGraphicsMode);
//         if (charWide > 0) {
//             strWidth += charWide + 1;
//         }
//         else if (charWide < 0) {
//             return;
//         }
//         if ((bX + strWidth) >= width || bY >= height)
//             return;
//         ptr++;
//     }
// }

// Modify drawString to preserve spaces
// void VirtualDMD::drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode)
// {
//     if (bX >= width || bY >= height)
//         return;
//     uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
//     if (bY + height < 0)
//         return;

//     int strWidth = 0;
//     const char* ptr = bChars;

//     Serial.println("Input string:");
//     for (int i = 0; i < length; i++) {
//         Serial.print((unsigned char)bChars[i], HEX);
//         Serial.print(" ");
//     }
//     Serial.println();

//     while (*ptr && (ptr - bChars) < length) {
//         int charWide; // Declare the variable here
//         unsigned char c = *ptr;
//         if ((c & 0x80) == 0) { // ASCII character
//             charWide = drawChar(bX + strWidth, bY, c, bGraphicsMode);
//             ptr++;
//         }
//         else { // UTF-8 sequence
//             c = mapUTF8ToCustom(ptr);
//             charWide = drawChar(bX + strWidth, bY, c, bGraphicsMode);
//             ptr++; // mapUTF8ToCustom already advanced the pointer for multi-byte sequences
//         }

//         if (charWide > 0) {
//             strWidth += charWide;
//             if (*(ptr) != '\0') { // Add space only if not at end of string
//                 strWidth += 1;    // Space between characters
//             }
//         }
//         else if (charWide < 0) {
//             return;
//         }

//         if ((bX + strWidth) >= width || bY >= height)
//             return;
//     }
// }

// void VirtualDMD::drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode)
// {
//     Serial.println("\n--- New drawString call ---");
//     Serial.print("String length: ");
//     Serial.println(length);
//     Serial.print("Full string hex dump: ");
//     for (int i = 0; i < length; i++) {
//         if ((unsigned char)bChars[i] < 0x10)
//             Serial.print("0");
//         Serial.print((unsigned char)bChars[i], HEX);
//         Serial.print(" ");
//     }
//     Serial.println();

//     if (bX >= width || bY >= height)
//         return;
//     uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
//     if (bY + height < 0)
//         return;

//     int strWidth = 0;
//     const char* ptr = bChars;

//     while (*ptr && (ptr - bChars) < length) {
//         int charWide;
//         unsigned char c = *ptr;

//         Serial.print("Processing character at position ");
//         Serial.print(ptr - bChars);
//         Serial.print(": 0x");
//         Serial.println(c, HEX);

//         if ((c & 0x80) == 0) { // ASCII character
//             charWide = drawChar(bX + strWidth, bY, c, bGraphicsMode);
//             ptr++;
//         }
//         else { // UTF-8 sequence
//             c = mapUTF8ToCustom(ptr);
//             charWide = drawChar(bX + strWidth, bY, c, bGraphicsMode);
//             ptr++; // mapUTF8ToCustom already advanced the pointer for multi-byte sequences
//         }

//         if (charWide > 0) {
//             strWidth += charWide;
//             if (*(ptr) != '\0' && (ptr - bChars) < length - 1) { // Add space only if not at end
//                 strWidth += 1;
//             }
//         }
//         else if (charWide < 0) {
//             return;
//         }

//         if ((bX + strWidth) >= width || bY >= height)
//             return;
//     }
// }

// void VirtualDMD::drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode)
// {
//     Serial.println("\n--- New drawString call ---");
//     Serial.print("String length: ");
//     Serial.println(length);
//     Serial.print("Full string hex dump: ");
//     for (int i = 0; i < length; i++) {
//         if ((unsigned char)bChars[i] < 0x10)
//             Serial.print("0");
//         Serial.print((unsigned char)bChars[i], HEX);
//         Serial.print(" ");
//     }
//     Serial.println();

//     if (bX >= width || bY >= height)
//         return;
//     uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
//     if (bY + height < 0)
//         return;

//     int strWidth = 0;
//     const char* ptr = bChars;

//     while (*ptr && (ptr - bChars) < length) {
//         int charWide;
//         unsigned char c = *ptr;

//         Serial.print("Processing character at position ");
//         Serial.print(ptr - bChars);
//         Serial.print(": 0x");
//         Serial.println(c, HEX);

//         if ((c & 0x80) == 0) { // ASCII character
//             charWide = drawChar(bX + strWidth, bY, c, bGraphicsMode);
//             ptr++; // Move one byte for ASCII
//         }
//         else { // UTF-8 sequence
//             c = mapUTF8ToCustom(ptr);
//             charWide = drawChar(bX + strWidth, bY, c, bGraphicsMode);
//             ptr += 2; // Move two bytes for UTF-8 sequence
//         }

//         if (charWide > 0) {
//             strWidth += charWide;
//             if (*(ptr) != '\0' && (ptr - bChars) < length - 1) { // Add space only if not at end
//                 strWidth += 1;
//             }
//         }
//         else if (charWide < 0) {
//             return;
//         }

//         if ((bX + strWidth) >= width || bY >= height)
//             return;
//     }
// }

// void VirtualDMD::drawString(int bX, int bY, const char* bChars, byte length, byte bGraphicsMode)
// {
//     if (bX >= width || bY >= height)
//         return;
//     uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
//     if (bY + height < 0)
//         return;

//     int strWidth = 0;
//     const char* ptr = bChars;

//     while (*ptr && (ptr - bChars) < length) {
//         int charWide;
//         unsigned char c = *ptr;

//         Serial.print("Processing character at position ");
//         Serial.print(ptr - bChars);
//         Serial.print(": 0x");
//         Serial.println(c, HEX);

//         if ((c & 0x80) == 0) { // ASCII character
//             charWide = drawChar(bX + strWidth, bY, c, bGraphicsMode);
//             ptr++; // Move one byte for ASCII
//         }
//         else {                        // UTF-8 sequence
//             const char* oldPtr = ptr; // Save current position
//             c = mapUTF8ToCustom(ptr); // ptr will be advanced inside mapUTF8ToCustom
//             charWide = drawChar(bX + strWidth, bY, c, bGraphicsMode);
//             if (ptr == oldPtr) { // if pointer wasn't advanced in mapUTF8ToCustom
//                 ptr++;           // advance by one as fallback
//             }
//         }

//         if (charWide > 0) {
//             strWidth += charWide;
//             if (*(ptr) != '\0' && (ptr - bChars) < length - 1) {
//                 strWidth += 1;
//             }
//         }
//         else if (charWide < 0) {
//             return;
//         }

//         if ((bX + strWidth) >= width || bY >= height)
//             return;
//     }
// }

void VirtualDMD::selectFont(const uint8_t* font)
{
    Font = font;
}

// int VirtualDMD::drawChar(int bX, int bY, const unsigned char letter, byte bGraphicsMode)
// {
//     Serial.print("Drawing character code: 0x");
//     Serial.println(letter, HEX);

//     if (bX >= width || bY >= height)
//         return -1;

//     // Map Turkish characters if needed
//     unsigned char c = mapTurkishChar(letter);

//     Serial.print("After Turkish mapping: 0x");
//     Serial.println(c, HEX);

//     uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
//     if (c == ' ') {
//         return getCustomWidth(' '); // Return the custom width for space
//     }

//     uint8_t width = 0;
//     uint8_t bytes = (height + 7) / 8;
//     uint8_t firstChar = pgm_read_byte(Font + FONT_FIRST_CHAR);
//     uint8_t charCount = pgm_read_byte(Font + FONT_CHAR_COUNT);
//     uint16_t index = 0;

//     // Handle extended characters (Turkish)
//     if (c >= 0x80) // If it's a Turkish character
//     {
//         int extendedIndex = (c - 0x80) + charCount; // Calculate position after standard characters
//         width = 5;                                  // Turkish characters use full width
//         index = extendedIndex * bytes * width + FONT_WIDTH_TABLE;
//     }
//     else // Standard ASCII character
//     {
//         if (c < firstChar || c >= (firstChar + charCount))
//             return 0;

//         c -= firstChar;

//         if (pgm_read_byte(Font + FONT_LENGTH) == 0 && pgm_read_byte(Font + FONT_LENGTH + 1) == 0) {
//             width = pgm_read_byte(Font + FONT_FIXED_WIDTH);
//             index = c * bytes * width + FONT_WIDTH_TABLE;
//         }
//         else {
//             for (uint8_t i = 0; i < c; i++) {
//                 index += pgm_read_byte(Font + FONT_WIDTH_TABLE + i);
//             }
//             index = index * bytes + charCount + FONT_WIDTH_TABLE;
//             width = pgm_read_byte(Font + FONT_WIDTH_TABLE + c);
//         }
//     }

//     if (bX < -width || bY < -height)
//         return width;

//     // Draw the character
//     for (uint8_t j = 0; j < width; j++) {
//         for (uint8_t i = bytes - 1; i < 254; i--) {
//             uint8_t data = pgm_read_byte(Font + index + j + (i * width));
//             int offset = (i * 8);
//             if ((i == bytes - 1) && bytes > 1) {
//                 offset = height - 8;
//             }
//             for (uint8_t k = 0; k < 8; k++) {
//                 if ((offset + k >= i * 8) && (offset + k <= height)) {
//                     if (data & (1 << k)) {
//                         writePixel(bX + j, bY + offset + k, bGraphicsMode, true);
//                     }
//                     else {
//                         writePixel(bX + j, bY + offset + k, bGraphicsMode, false);
//                     }
//                 }
//             }
//         }
//     }

//     // Return the actual visual width for proper spacing
//     return getCustomWidth(letter);
// }

int VirtualDMD::drawChar(int bX, int bY, const unsigned char letter, byte bGraphicsMode)
{
    unsigned char c = mapTurkishChar(letter);

    if (bX >= width || bY >= height)
        return -1;
    // unsigned char c = letter;
    uint8_t height = pgm_read_byte(Font + FONT_HEIGHT);
    if (c == ' ') {
        int charWide = charWidth(' ');
        return charWide;
    }
    uint8_t width = 0;
    uint8_t bytes = (height + 7) / 8;

    uint8_t firstChar = pgm_read_byte(Font + FONT_FIRST_CHAR);
    uint8_t charCount = pgm_read_byte(Font + FONT_CHAR_COUNT);

    uint16_t index = 0;

    if (c < firstChar || c >= (firstChar + charCount))
        return 0;
    c -= firstChar;

    if (pgm_read_byte(Font + FONT_LENGTH) == 0 && pgm_read_byte(Font + FONT_LENGTH + 1) == 0) {
        width = pgm_read_byte(Font + FONT_FIXED_WIDTH);
        index = c * bytes * width + FONT_WIDTH_TABLE;
    }
    else {
        for (uint8_t i = 0; i < c; i++) {
            index += pgm_read_byte(Font + FONT_WIDTH_TABLE + i);
        }
        index = index * bytes + charCount + FONT_WIDTH_TABLE;
        width = pgm_read_byte(Font + FONT_WIDTH_TABLE + c);
    }
    if (bX < -width || bY < -height)
        return width;

    // Draw the character
    for (uint8_t j = 0; j < width; j++) {
        for (uint8_t i = bytes - 1; i < 254; i--) {
            uint8_t data = pgm_read_byte(Font + index + j + (i * width));
            int offset = (i * 8);
            if ((i == bytes - 1) && bytes > 1) {
                offset = height - 8;
            }
            for (uint8_t k = 0; k < 8; k++) {
                if ((offset + k >= i * 8) && (offset + k <= height)) {
                    if (data & (1 << k)) {
                        writePixel(bX + j, bY + offset + k, bGraphicsMode, true);
                    }
                    else {
                        writePixel(bX + j, bY + offset + k, bGraphicsMode, false);
                    }
                }
            }
        }
    }
    return width;
}

// int VirtualDMD::charWidth(const unsigned char letter)
// {
//     unsigned char c = letter;
//     if (c == ' ')
//         c = 'n';
//     uint8_t width = 0;

//     uint8_t firstChar = pgm_read_byte(Font + FONT_FIRST_CHAR);
//     uint8_t charCount = pgm_read_byte(Font + FONT_CHAR_COUNT);

//     if (c < firstChar || c >= (firstChar + charCount)) {
//         return 0;
//     }
//     c -= firstChar;

//     if (pgm_read_byte(Font + FONT_LENGTH) == 0 && pgm_read_byte(Font + FONT_LENGTH + 1) == 0) {
//         width = pgm_read_byte(Font + FONT_FIXED_WIDTH);
//     }
//     else {
//         width = pgm_read_byte(Font + FONT_WIDTH_TABLE + c);
//     }
//     return width;
// }

int VirtualDMD::charWidth(const unsigned char letter)
{
    unsigned char c = letter;
    Serial.print("Getting width for '");
    Serial.print((char)letter);
    Serial.print("': ");

    if (c == ' ') {
        c = 'n';
        Serial.print("(space, using 'n') ");
    }

    uint8_t width = 0;
    uint8_t firstChar = pgm_read_byte(Font + FONT_FIRST_CHAR);
    uint8_t charCount = pgm_read_byte(Font + FONT_CHAR_COUNT);

    if (c < firstChar || c >= (firstChar + charCount)) {
        Serial.println("0 (out of range)");
        return 0;
    }

    c -= firstChar;

    if (pgm_read_byte(Font + FONT_LENGTH) == 0 && pgm_read_byte(Font + FONT_LENGTH + 1) == 0) {
        width = pgm_read_byte(Font + FONT_FIXED_WIDTH);
        Serial.print("fixed width=");
    }
    else {
        width = pgm_read_byte(Font + FONT_WIDTH_TABLE + c);
        Serial.print("variable width=");
    }

    Serial.println(width);
    return width;
}

std::vector<std::vector<int>> VirtualDMD::getGrid() const
{
    std::vector<std::vector<int>> result(height, std::vector<int>(width, 0));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            result[y][x] = grid[y][x] ? 1 : 0;
        }
    }
    return result;
}

// std::vector<std::vector<int>> stringToLEDGrid(const char* bChars, byte length, int left, int top, int totalRows)
// {
//     return generateFlexibleGrid(bChars, length, left, top, totalRows);
// }

std::vector<std::vector<int>> stringToLEDGrid(const char* bChars, byte length, int left, int top, int totalRows)
{
    return generateFlexibleGrid(bChars, length, left, top, totalRows);
}

std::vector<std::vector<int>> generateFlexibleGrid(const char* text, int length, int left, int top, int totalRows)
{
    // First, generate the 8x64 grid
    VirtualDMD vdmd(2, 1); // 2 displays across, 1 display down (8x64)
    vdmd.selectFont(System5x7);
    vdmd.drawString(left, top, text, length, GRAPHICS_NORMAL);
    auto baseGrid = vdmd.getGrid();

    // Ensure we have at least 8 rows and no more than 64
    totalRows = std::max(8, std::min(totalRows, 64));

    // Create the final grid with the desired number of rows
    std::vector<std::vector<int>> finalGrid(totalRows, std::vector<int>(64, 0));

    // Copy the base grid (which is 8x64) into the final grid
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 64; ++j) {
            finalGrid[i][j] = baseGrid[i][j];
        }
    }

    // The remaining rows (if any) are already filled with zeros

    return finalGrid;
}

unsigned char VirtualDMD::mapTurkishChar(unsigned char c)
{
    switch (c) {
    case 0xC4: return TURKISH_I_dotted;   // İ
    case 0xE7: return TURKISH_c_cedil;    // ç
    case 0xC7: return TURKISH_C_cedil;    // Ç
    case 0x11F: return TURKISH_g_breve;   // ğ
    case 0x11E: return TURKISH_G_breve;   // Ğ
    case 0x131: return TURKISH_i_dotless; // ı
    case 0xF6: return TURKISH_o_diaer;    // ö
    case 0xD6: return TURKISH_O_diaer;    // Ö
    case 0x15F: return TURKISH_s_cedil;   // ş
    case 0x15E: return TURKISH_S_cedil;   // Ş
    case 0xFC: return TURKISH_u_diaer;    // ü
    case 0xDC: return TURKISH_U_diaer;    // Ü
    default: return c;
    }
}

// In your cpp file (strtovector_converter.cpp)
int VirtualDMD::getCustomWidth(unsigned char c)
{
    // First map Turkish characters if needed
    c = mapTurkishChar(c);

    // Adjust for array index
    if (c >= 0x20 && c < 0x20 + CUSTOM_WIDTHS_SIZE) {
        return customWidths[c - 0x20];
    }
    return 5; // Default width for unknown characters
}

unsigned char VirtualDMD::mapUTF8ToCustom(const char*& text)
{
    unsigned char c = (unsigned char)*text;

    Serial.print("Processing byte: 0x");
    Serial.println(c, HEX);

    // If it's not a UTF-8 multi-byte sequence, return as is
    if ((c & 0x80) == 0) {
        return c;
    }

    // Get second byte of UTF-8 sequence
    unsigned char c2 = (unsigned char)*(text + 1);
    Serial.print("Second byte: 0x");
    Serial.println(c2, HEX);

    // Two-byte UTF-8 sequence
    if ((c & 0xE0) == 0xC0) {
        if (c == 0xC3) {
            text += 2; // Advance pointer past the 2-byte sequence
            switch (c2) {
            case 0xBC: Serial.println("Found ü"); return TURKISH_u_diaer;   // ü (C3 BC)
            case 0x9C: Serial.println("Found Ü"); return TURKISH_U_diaer;   // Ü (C3 9C)
            case 0xB6: Serial.println("Found ö"); return TURKISH_o_diaer;   // ö (C3 B6)
            case 0x96: Serial.println("Found Ö"); return TURKISH_O_diaer;   // Ö (C3 96)
            case 0xA7: Serial.println("Found ç"); return TURKISH_c_cedil;   // ç (C3 A7)
            case 0x87: Serial.println("Found Ç"); return TURKISH_C_cedil;   // Ç (C3 87)
            case 0xB1: Serial.println("Found ı"); return TURKISH_i_dotless; // ı (C3 B1)
            case 0x84: Serial.println("Found İ"); return TURKISH_I_dotted;  // İ (C3 84)
            }
        }
        else if (c == 0xC4) {
            text += 2;
            switch (c2) {
            case 0x9F: Serial.println("Found ğ"); return TURKISH_g_breve; // ğ (C4 9F)
            case 0x9E: Serial.println("Found Ğ"); return TURKISH_G_breve; // Ğ (C4 9E)
            }
        }
        else if (c == 0xC5) {
            text += 2;
            switch (c2) {
            case 0x9F: Serial.println("Found ş"); return TURKISH_s_cedil; // ş (C5 9F)
            case 0x9E: Serial.println("Found Ş"); return TURKISH_S_cedil; // Ş (C5 9E)
            }
        }
    }

    Serial.println("Unrecognized sequence");
    return '?'; // Return question mark for unrecognized sequences
}

// Add to your implementation file:
const uint8_t VirtualDMD::customWidths[] = {
  // ASCII characters (starting from space, 0x20)
  3, // Space
  2, // !
  3, // "
  5, // #
  5, // $
  5, // %
  5, // &
  2, // '
  3, // (
  3, // )
  5, // *
  5, // +
  3, // ,
  5, // -
  2, // .
  5, // /
  5, // 0-9
  5, 5, 5, 5, 5, 5, 5, 5, 5,
  2, // :
  2, // ;
  4, // <
  5, // =
  4, // >
  5, // ?
  5, // @
  5, // A-Z
  5, 5, 5, 5, 5, 5, 5, 3, 5, 5, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  3, // [
  5, // \
    3,  // ]
  4, // ^
  5, // _
  3, // `
  5, // a-z
  5, 4, 5, 5, 4, 5, 5, 2, 3, 4, 2, 5, 5, 5, 5, 5, 4, 5, 3, 5, 5, 5, 5, 5, 5,

  // Turkish characters
  2, // ı (dotless i)
  3, // İ (dotted I)
  5, // ğ
  5, // Ğ
  5, // ü
  5, // Ü
  4, // ş
  5, // Ş
  5, // ö
  5, // Ö
  4, // ç
  5  // Ç
};