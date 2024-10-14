#include "charge_animations.hpp"

void anim_StationReserved(PatternAnimator& p10, double cycle)
{
    int ROW_START = 4;
    int COL_START = 23;
    int msdelay = 250;

    // hourglass frame
    p10.draw_pattern_static(p10.hourglass, ROW_START, COL_START);
    // animation loop
    // while(cycle > 0)
    // {
    ROW_START = 5;
    COL_START = 26;
    p10.draw_pattern_static(p10.hourglass_anim_start, ROW_START, COL_START);
    delay(msdelay);
    p10.delete_pattern_static(p10.hourglass_anim_start, ROW_START, COL_START);
    p10.draw_pattern_static(p10.hourglass_anim_phase_first, ROW_START, COL_START);
    delay(msdelay);
    p10.delete_pattern_static(p10.hourglass_anim_phase_first, ROW_START, COL_START);
    p10.draw_pattern_static(p10.hourglass_anim_phase_second, ROW_START, COL_START);
    delay(msdelay);
    p10.delete_pattern_static(p10.hourglass_anim_phase_second, ROW_START, COL_START);
    p10.draw_pattern_static(p10.hourglass_anim_phase_third, ROW_START, COL_START);
    delay(msdelay);
    p10.delete_pattern_static(p10.hourglass_anim_phase_third, ROW_START, COL_START);
    p10.draw_pattern_static(p10.hourglass_anim_phase_last, ROW_START, COL_START);
    delay(msdelay);
    // --cycle;
    // }
}

void anim_StationWaiting(PatternAnimator& p10, double cycle)
{
    int ROW_START = 4;
    int COL_START = 0;
    int PANEL_LAST_COL = 49;
    int msdelay = 4000;
    int delaystep = 25;
    p10.draw_pattern_tetris(p10.xsarj, ROW_START, COL_START, PANEL_LAST_COL, msdelay, cycle);
    p10.dmd->clearScreen(true);
    COL_START = 49;
    p10.draw_pattern_scrolling(p10.xsarj, ROW_START, COL_START, delaystep, cycle);
}

// *********************************
// Station Stopped( chargehandle )
// *********************************

void anim_StationError(PatternAnimator& p10, double cycle)
{
    int ROW_START = 4;
    int COL_START = 0;
    int msdelay = 0;
    int delaystep = 0;

    // lambda functions for the threads
    auto parallel_drawer_chargehandle = [](PatternAnimator& p10, int msdelay, double cycle) -> void {
        cycle += 16;
        int ROW_START = 4;
        int COL_START = 41;

        // while(cycle > 0)
        // {
        p10.draw_pattern_static(p10.chargehandle_frame_1, ROW_START, COL_START);
        delay(msdelay);
        p10.draw_pattern_static(p10.chargehandle_frame_2, ROW_START, COL_START);
        delay(msdelay);
        p10.draw_pattern_static(p10.chargehandle_frame_3, ROW_START, COL_START);
        delay(msdelay);
        //     --cycle;
        // }
    };

    auto parallel_drawer_cable = [](PatternAnimator& p10, int msdelay, double cycle) -> void {
        cycle += 6;
        int ROW_START = 4;
        int COL_START = 26;

        // while(cycle > 0)
        // {
        p10.draw_pattern_static(p10.chargehandle_cable_frame_1, ROW_START, COL_START);
        delay(msdelay);
        p10.draw_pattern_static(p10.chargehandle_cable_frame_2, ROW_START, COL_START);
        delay(msdelay);
        //     --cycle;
        // }
    };

    auto parallel_drawer_excmark = [](PatternAnimator& p10, int msdelay, double cycle) -> void {
        int ROW_START = 4;
        int COL_START = 3;

        p10.draw_pattern_blinking(p10.excmark_little, ROW_START, COL_START, msdelay, cycle);
    };

    // std::ref() must be used if we are passing a reference because thread arguments are moved/copied by value.
    // We can't copy a reference, we can copy the object that it refers to.
    msdelay = 40;
    std::thread thread_chargehandle(parallel_drawer_chargehandle, std::ref(p10), msdelay, cycle);

    msdelay = 140;
    std::thread thread_cable(parallel_drawer_cable, std::ref(p10), msdelay, cycle);

    // ROW_START = 4;
    // COL_START = 3;
    msdelay = 200;
    std::thread thread_excmark(parallel_drawer_excmark, std::ref(p10), msdelay, cycle);

    thread_chargehandle.join();
    thread_cable.join();
    thread_excmark.join();
}

void anim_StationCharge_Starting(PatternAnimator& p10)
{
    for (int cycle = 0; cycle < 1; ++cycle)
        {
            p10.dmd->drawMarquee("Sarj Basliyor", 13, (32 * DISPLAYS_ACROSS) - 1, 4);
            long start = millis();
            long timer = start;
            boolean ret = false;
            while (!ret)
                {
                    if ((timer + 21) < millis())
                        {
                            ret = p10.dmd->stepMarquee(-1, 0);
                            timer = millis();
                        }
                }
        }
}

void anim_StationCharge_Started(PatternAnimator& p10)
{
    for (int cycle = 0; cycle < 1; ++cycle)
        {
            p10.dmd->drawMarquee("Sarj Basladi", 12, (32 * DISPLAYS_ACROSS) - 1, 4);
            long start = millis();
            long timer = start;
            boolean ret = false;
            while (!ret)
                {
                    if ((timer + 21) < millis())
                        {
                            ret = p10.dmd->stepMarquee(-1, 0);
                            timer = millis();
                        }
                }
        }
}

void anim_StationCharge_Stopped(PatternAnimator& p10)
{
    for (int cycle = 0; cycle < 1; ++cycle)
        {
            p10.dmd->drawMarquee("Sarj Sonlandirildi", 18, (32 * DISPLAYS_ACROSS) - 1, 4);
            long start = millis();
            long timer = start;
            boolean ret = false;
            while (!ret)
                {
                    if ((timer + 21) < millis())
                        {
                            ret = p10.dmd->stepMarquee(-1, 0);
                            timer = millis();
                        }
                }
        }
}

void anim_InsertSocket(PatternAnimator& p10, double cycle)
{
    for (int cycle = 0; cycle < 1; ++cycle)
        {
            p10.dmd->drawMarquee("Soketi Takin", 12, (32 * DISPLAYS_ACROSS) - 1, 4);
            long start = millis();
            long timer = start;
            boolean ret = false;
            while (!ret)
                {
                    if ((timer + 21) < millis())
                        {
                            ret = p10.dmd->stepMarquee(-1, 0);
                            timer = millis();
                        }
                }
        }
}

void anim_StationCharge_Charging(PatternAnimator& p10, double cycle)
{
    int ROW_START = 4;
    int COL_START = 0;
    int delaystep = 35;
    int PATTERN_DISTANCE = 1;

    // // Clear the pattern_pack vector before adding new elements
    // p10.pattern_pack.clear();
    // p10.pattern_pack.push_back(p10.arrow_large);
    // p10.pattern_pack.push_back(p10.arrow_large);
    // p10.pattern_pack.push_back(p10.arrow_large);
    // p10.draw_pattern_scrolling_accumulator_series(p10.pattern_pack, ROW_START, COL_START, PATTERN_DISTANCE, delaystep, cycle);

    p10.draw_pattern_scrolling(p10.lightning, ROW_START, COL_START, delaystep, cycle);
}

void anim_charge_battery(PatternAnimator& p10, int slice)
{
    p10.draw_pattern_static(p10.bat_full, 4, 0);
}

void anim_StationWaiting_custom(PatternAnimator& p10, const char* bChars, byte length)
{
    p10.dmd->drawMarquee(bChars, length, (32 * DISPLAYS_ACROSS) - 1, 4);
    long start = millis();
    long timer = start;
    boolean ret = false;
    while (!ret)
        {
            if ((timer + 21) < millis())
                {
                    ret = p10.dmd->stepMarquee(-1, 0);
                    timer = millis();
                }
        }
}
