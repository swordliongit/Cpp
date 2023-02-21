

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
    // for series
    static std::vector<std::vector<int>> arrow_single;
    static std::vector<std::vector<int>> lightning;
    static std::vector<std::vector<int>> excmark_little;
    static std::vector<std::vector<int>> spaceship;
    static std::vector<std::vector<int>> claw;
    static std::vector<std::vector<int>> stripe;
    // 7x7
    // for rotation
    static std::vector<std::vector<int>> sword;
    static std::vector<std::vector<int>> bomb;
    static std::vector<std::vector<int>> robot;
    static std::vector<std::vector<int>> excmark_45;
    // 7x50
    static std::vector<std::vector<int>> chargehandle;
    static std::vector<std::vector<int>> chargehandle_lightning;
    
    // 7x10
    static std::vector<std::vector<int>> xmark;

    static std::vector<std::vector<std::vector<int>>> pattern_pack;

    
    // member functions
    // basic
    void draw_pattern_static(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START);
    void delete_pattern_static(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START);
    void draw_pattern_blinking(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int msdelay, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, float delaystep, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_rotating(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, float delaystep, double cycle=std::numeric_limits<double>::infinity());
    // advanced drawers
    void draw_pattern_tetris(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PANEL_LAST_COL, int msdelay, double cycle=std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_series(std::vector<std::vector<std::vector<int>>> pattern_pack, int ROW_START, int COL_START, int PATTERN_DISTANCE, float delaystep, double cycle=std::numeric_limits<double>::infinity());
    void rotate_matrix_90(std::vector<std::vector<int>>& matrix);
};




#endif