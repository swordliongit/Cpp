

#ifndef P10_ANIMATIONS_KILICARSLAN_H
#define P10_ANIMATIONS_KILICARSLAN_H
#include <Arduino.h>
#include <DMD32.h>   


class PatternAnimator
{
    DMD *dmd;

public:

    PatternAnimator(DMD *dmdinitialized)
    {
        this->dmd = dmdinitialized;
    }

    void draw_blinking_pattern(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PATTERN_ROW_MAX, int PATTERN_COL_MAX, int msdelay, int cycle);
    void draw_scrolling_pattern(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PATTERN_ROW_MAX, int PATTERN_COL_MAX, int pxjmp_step, int cycle);
};


#endif