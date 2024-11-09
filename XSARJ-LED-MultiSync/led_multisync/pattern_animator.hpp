#ifndef PATTERN_ANIMATOR_H
#define PATTERN_ANIMATOR_H
#include <Arduino.h>
#include <DMD32.h>
#include <limits>
#include <vector>

class PatternAnimator {
  public:
    DMD* dmd;
    PatternAnimator(DMD* dmdinitialized)
    {
        this->dmd = dmdinitialized;
    }

    // multi-sync patterns
    static std::vector<std::vector<int>> mask;
    static std::vector<std::vector<int>> line;
    static std::vector<std::vector<int>> grid_turned_off;
    static std::vector<std::vector<int>> square;
    static std::vector<std::vector<int>> square_32;
    static std::vector<std::vector<int>> grid_32;
    // 64x64
    static std::vector<std::vector<int>> ball_64;

    // 7x35
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
    // 6x54
    static std::vector<std::vector<int>> insert_socket;
    // 7x52
    static std::vector<std::vector<int>> ekintarim;
    // 10x20
    static std::vector<std::vector<int>> wifi_offline;

    // 8x64
    static std::vector<std::vector<int>> bat_full;

    // 8x64
    static std::vector<std::vector<int>> bat_7;
    // 8x64
    static std::vector<std::vector<int>> bat_6;
    // 8x64
    static std::vector<std::vector<int>> Battery;

    static std::vector<std::vector<std::vector<int>>> pattern_pack;

    // member functions
    // basic
    void draw_pattern_static(std::vector<std::vector<int>>& pattern, int ROW_START, int COL_START);
    void delete_pattern_static(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START);
    void draw_pattern_blinking(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int msdelay,
                               double cycle = std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, float delaystep,
                                double cycle = std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_rotating(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, float delaystep,
                                         double cycle = std::numeric_limits<double>::infinity());
    // advanced
    void draw_pattern_tetris(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PANEL_LAST_COL, int msdelay,
                             double cycle = std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_series(std::vector<std::vector<std::vector<int>>> pattern_pack, int ROW_START, int COL_START, int PATTERN_DISTANCE,
                                       float delaystep, double cycle = std::numeric_limits<double>::infinity());
    void draw_pattern_scrolling_accumulator_series(std::vector<std::vector<std::vector<int>>> pattern_pack, int ROW_START, int COL_START,
                                                   int PATTERN_DISTANCE, float delaystep, double cycle = std::numeric_limits<double>::infinity());
    // helper functions
    void rotate_matrix_90(std::vector<std::vector<int>>& matrix);
};

#endif