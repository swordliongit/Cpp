#ifndef PATTERN_SHIFTER_H
#define PATTERN_SHIFTER_H

#include <vector>

class PatternShifter {
  private:
    const std::vector<std::vector<int>>& pattern;
    int offsetX;
    int offsetY;

  public:
    PatternShifter(const std::vector<std::vector<int>>& grid) : pattern(grid), offsetX(0), offsetY(0) {}

    void shiftLeft()
    {
        offsetX = std::min(offsetX + 1, static_cast<int>(pattern[0].size()));
    }

    void shiftRight()
    {
        offsetX = std::max(offsetX - 1, -static_cast<int>(pattern[0].size()));
    }

    void shiftUp()
    {
        offsetY = std::max(offsetY - 1, -static_cast<int>(pattern.size()));
    }

    void shiftDown()
    {
        offsetY = std::min(offsetY + 1, static_cast<int>(pattern.size()));
    }

    std::vector<std::vector<int>> getDisplayFrame(int rows, int cols) const
    {
        std::vector<std::vector<int>> frame(rows, std::vector<int>(cols, 0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int patternRow = i - offsetY;
                int patternCol = j + offsetX;
                if (patternRow >= 0 && patternRow < pattern.size() && patternCol >= 0 && patternCol < pattern[0].size()) {
                    frame[i][j] = pattern[patternRow][patternCol];
                }
            }
        }
        return frame;
    }
};

#endif