

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

    // for series
    // 7x4
    static std::vector<std::vector<int>> arrow_small;
    static std::vector<std::vector<int>> arrow_mid;
    static std::vector<std::vector<int>> arrow_large;

    static std::vector<std::vector<int>> lightning;
    // 7x18
    static std::vector<std::vector<int>> excmark_little;
    
    // 7x7
    // for rotation
    static std::vector<std::vector<int>> bomb;

    // 7x20
    static std::vector<std::vector<int>> chargehandle_frame_1;
    static std::vector<std::vector<int>> chargehandle_frame_2;
    static std::vector<std::vector<int>> chargehandle_frame_3;
    // 7x15
    static std::vector<std::vector<int>> chargehandle_cable_frame_1;
    static std::vector<std::vector<int>> chargehandle_cable_frame_2;

    static std::vector<std::vector<std::vector<int>>> pattern_pack;

    
    // member functions
    // basic
    void draw_pattern_static(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START);
    void delete_pattern_static(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START);
    void draw_pattern_blinking(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int msdelay, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, float delaystep, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_rotating(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, float delaystep, double cycle=std::numeric_limits<double>::infinity());
    // advanced
    void draw_pattern_tetris(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PANEL_LAST_COL, int msdelay, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_series(std::vector<std::vector<std::vector<int>>> pattern_pack, int ROW_START, int COL_START, int PATTERN_DISTANCE, float delaystep, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_accumulator_series(std::vector<std::vector<std::vector<int>>> pattern_pack, int ROW_START, int COL_START, int PATTERN_DISTANCE, float delaystep, double cycle=std::numeric_limits<double>::infinity());

    // helper functions
    void rotate_matrix_90(std::vector<std::vector<int>>& matrix);
};




#endif