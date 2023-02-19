

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

    // patterns

    //16x64
    static std::vector<std::vector<int>> xsarj_full;
    //7x35
    static std::vector<std::vector<int>> xsarj;
    // 7x64
    static std::vector<std::vector<int>> excmark;
    // 7x20
    static std::vector<std::vector<int>> hourglass;
    // 5x14
    static std::vector<std::vector<int>> hourglass_anim_start;
    static std::vector<std::vector<int>> hourglass_anim_phase_first;
    static std::vector<std::vector<int>> hourglass_anim_phase_second;
    static std::vector<std::vector<int>> hourglass_anim_phase_third;
    static std::vector<std::vector<int>> hourglass_anim_phase_last;
    // 7x24
    static std::vector<std::vector<int>> lightning_arrow;
    // 7x11
    static std::vector<std::vector<int>> arrow_single;
    static std::vector<std::vector<int>> lightning;
    // 7x50
    static std::vector<std::vector<int>> chargehandle;
    static std::vector<std::vector<int>> chargehandle_lightning;
    static std::vector<std::vector<int>> excmark_little;

    static std::vector<std::vector<std::vector<int>>> pattern_pack;
    
    // member functions
    void draw_pattern_blinking(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int msdelay, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int pxjmp_step, int delaystep, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_disjoint(std::vector<std::vector<int>> pattern_first, std::vector<std::vector<int>> pattern_second, int ROW_START, int COL_START, int PATTERN_DISTANCE, int pxjmp_step, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_static(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START);
    void delete_pattern_static(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START);
    void draw_pattern_tetris(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PANEL_LAST_COL, int pxjmp_step, int msdelay, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_pack(std::vector<std::vector<std::vector<int>>> pattern_pack, int ROW_START, int COL_START, int PATTERN_ROW_MAX, int PATTERN_COL_MAX, int pxjmp_step, double cycle=std::numeric_limits<double>::infinity());
};

#endif