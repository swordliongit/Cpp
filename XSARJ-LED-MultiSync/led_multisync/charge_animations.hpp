#ifndef CHARGE_ANIMATIONS_H
#define CHARGE_ANIMATIONS_H

#include <limits> // for numeric_limits
#include <thread>
#include "util.hpp"

void anim_StationReserved(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity());

void anim_StationWaiting(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity());

// *********************************
// Station Stopped( chargehandle )
// *********************************
void anim_StationError(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity());


void anim_StationCharge_Starting(PatternAnimator& p10);


void anim_StationCharge_Started(PatternAnimator& p10);


void anim_StationCharge_Stopped(PatternAnimator& p10);


void anim_InsertSocket(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity());


void anim_StationCharge_Charging(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity());


void anim_StationWaiting_custom(PatternAnimator& p10, const char* bChars, byte length);

#endif
