

#include "p10_animations_kilicarslan.h"
#include <DMD32.h>  

// Pattern definitions

std::vector<std::vector<int>> PatternAnimator::xsarj_full =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1,0,1,0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

std::vector<std::vector<int>> PatternAnimator::xsarj = 
{
    {1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1},
    {0,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,1},
    {0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,0,0,1,1},
    {0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,1,1},
    {0,0,1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,1,1},
    {0,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1,0,1,0,0,1,1,0,1,1,0,1,1},
    {1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1}
};

// 7x64
std::vector<std::vector<int>> PatternAnimator::excmark = 
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0}
};

std::vector<std::vector<int>> PatternAnimator::hourglass = 
{
	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
	{1,0,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,1},
	{1,0,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,0,1},
	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1}
};
std::vector<std::vector<int>> PatternAnimator::hourglass_anim_start =
{
	{0,0,0,1,1,0,0,0,0,1,1,0,1,0},
	{1,0,0,0,0,1,1,1,1,1,0,1,0,0},
	{0,1,0,1,0,0,1,0,1,0,1,0,1,0},
	{1,0,0,0,0,1,1,1,1,1,0,1,0,0},
	{0,0,0,1,1,0,0,0,0,1,1,0,1,0}
};
std::vector<std::vector<int>> PatternAnimator::hourglass_anim_phase_first = 
{
	{1,0,0,1,1,0,0,0,0,1,1,1,0,0},
	{0,1,0,0,0,1,1,1,1,0,1,0,0,0},
	{1,0,1,0,1,0,0,1,0,1,0,1,0,0},
	{0,1,0,0,0,1,1,1,1,0,1,0,0,0},
	{1,0,0,1,1,0,0,0,0,1,1,1,0,0}
};
std::vector<std::vector<int>> PatternAnimator::hourglass_anim_phase_second =
{
	{1,0,1,1,1,0,0,0,0,1,1,0,0,0},
	{0,1,0,0,0,1,1,1,1,1,0,0,0,0},
	{1,0,1,0,1,0,1,0,1,0,1,0,0,0},
	{0,1,0,0,0,1,1,1,1,1,0,0,0,0},
	{1,0,1,1,1,0,0,0,0,1,1,0,0,0}
};
std::vector<std::vector<int>> PatternAnimator::hourglass_anim_phase_third =
{
    {1,0,1,1,1,0,0,0,0,1,1,0,0,0},
    {0,1,0,1,0,1,1,1,1,0,0,0,0,0},
    {1,0,1,0,0,1,0,1,0,1,0,0,0,0},
    {0,1,0,1,0,1,1,1,1,0,0,0,0,0},
    {1,0,1,1,1,0,0,0,0,1,1,0,0,0}
};
std::vector<std::vector<int>> PatternAnimator::hourglass_anim_phase_last =
{
    {1,0,1,1,1,0,0,0,0,1,1,0,0,0},
    {0,1,0,1,0,1,1,1,1,0,0,0,0,0},
    {1,0,1,0,1,0,1,0,1,0,0,0,0,0},
    {0,1,0,1,0,1,1,1,1,0,0,0,0,0},
    {1,0,1,1,1,0,0,0,0,1,1,0,0,0}
};

std::vector<std::vector<int>> PatternAnimator::lightning_arrow = 
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0}
};

// 7x11
std::vector<std::vector<int>> PatternAnimator::arrow_single = 
{
	{1,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0}
};
// 7x11
std::vector<std::vector<int>> PatternAnimator::lightning = {
	{0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,1,1,1,0,0,0,0,1},
	{0,0,1,1,1,1,0,0,1,1,0},
	{0,1,1,1,0,1,0,1,1,0,0},
	{1,1,1,0,0,1,1,1,0,0,0},
	{1,0,0,0,0,1,1,0,0,0,0}
};

std::vector<std::vector<std::vector<int>>> PatternAnimator::pattern_pack =
{
    {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
        {0,0,1,0,1,0,0,0,0,0,0,0,1,0,0},
        {0,1,0,0,0,1,0,0,0,0,0,1,0,0,0},
        {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}
    },
    
    {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1},
        {0,0,1,0},
        {0,1,0,0},
        {1,0,0,0}
    },
};

// 7x50
std::vector<std::vector<int>> PatternAnimator::chargehandle = 
{
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
	{0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1},
	{0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1},
	{0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0}
};
// // 7x50
// std::vector<std::vector<int>> PatternAnimator::chargehandle_lightning =
// {
// 	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
// 	{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
// 	{0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
// 	{0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1},
// 	{0,1,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,1},
// 	{1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0},
// 	{1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
// };
// 7x36
std::vector<std::vector<int>> PatternAnimator::chargehandle_lightning =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,0},
	{0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
	{1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0}
};

std::vector<std::vector<int>> PatternAnimator::excmark_little =
{
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,1,1,1,1,1,1,1},
	{1,1,0,0,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0}
};
	

// Function definitions
void PatternAnimator::draw_pattern_blinking(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int msdelay, double cycle)
{
	int PATTERN_ROW_MAX = pattern.size();
	int PATTERN_COL_MAX = pattern[0].size();
    while(cycle > 0)
	{
		// draw the pattern
		for(int row=ROW_START, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
		{
			for(int col=COL_START, colindex=0; colindex<PATTERN_COL_MAX; --col, ++colindex)
			{
				dmd->writePixel(col, row, GRAPHICS_NORMAL, pattern[rowindex][colindex]);
			}
			// dmd.writePixel(63-pxjmp_step+1, row, GRAPHICS_NORMAL, 0);
		}
		
		delay(msdelay);
		
		// delete the pattern
		for(int row=ROW_START, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
		{
			for(int col=COL_START, colindex=0; colindex<PATTERN_COL_MAX; --col, ++colindex)
			{
				dmd->writePixel(col, row, GRAPHICS_NORMAL, 0);
			}
		}

		--cycle;
		delay(msdelay);
	}
}


void PatternAnimator::draw_pattern_scrolling(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int pxjmp_step, int delaystep, double cycle)
{
	int PATTERN_ROW_MAX = pattern.size();
	int PATTERN_COL_MAX = pattern[0].size();
	float step = delaystep;
	while(cycle > 0)
	{
		// draw the pattern
		for(int row=ROW_START, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
		{
			for(int col=COL_START-pxjmp_step, colindex=0; colindex<PATTERN_COL_MAX; --col, ++colindex)
			{
				dmd->writePixel(col, row, GRAPHICS_NORMAL, pattern[rowindex][colindex]);
			}
		// dmd.writePixel(63-pxjmp_step+1, row, GRAPHICS_NORMAL, 0);
		}

		delay(1.0f+ delaystep);
		if(!(delaystep < 12))
		{
			delaystep = delaystep-0.6f;
		}
		
		// delete the pattern
		for(int row=ROW_START, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
		{
			for(int col=COL_START-pxjmp_step, colindex=0; colindex<PATTERN_COL_MAX; --col, ++colindex)
			{
				dmd->writePixel(col, row, GRAPHICS_NORMAL, 0);
			}
		}
		// shift the pixels by 1 bit
		pxjmp_step = pxjmp_step + 1;
		// start from the beginning
		if(pxjmp_step == 64 + (PATTERN_COL_MAX * 2) + PATTERN_COL_MAX)
		{
			pxjmp_step = 0;
			delaystep = step;

			--cycle;
		}
	}
}


void PatternAnimator::draw_pattern_scrolling_disjoint(std::vector<std::vector<int>> pattern_first, std::vector<std::vector<int>> pattern_second, int ROW_START, int COL_START, int PATTERN_DISTANCE, int pxjmp_step, double cycle)
{
	int PATTERN_ROW_MAX = pattern_first.size();
	int PATTERN_COL_MAX = pattern_first[0].size();
	float step = 35;
	while(cycle > 0)
	{
		// draw the pattern
		for(int row=ROW_START, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
		{
			for(int col=COL_START-pxjmp_step, colindex=0; colindex<PATTERN_COL_MAX; --col, ++colindex)
			{
				dmd->writePixel(col, row, GRAPHICS_NORMAL, pattern_first[rowindex][colindex]);
				if(pxjmp_step > PATTERN_DISTANCE)
				{
					dmd->writePixel(col+PATTERN_COL_MAX*2, row, GRAPHICS_NORMAL, pattern_second[rowindex][colindex]);
				}
			}
		// dmd.writePixel(63-pxjmp_step+1, row, GRAPHICS_NORMAL, 0);
		}

		delay(1.0f+ step);
		if(!(step < 12))
		{
			step = step-0.6f;
		}
		
		// delete the pattern
		for(int row=ROW_START, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
		{
			for(int col=COL_START-pxjmp_step, colindex=0; colindex<PATTERN_COL_MAX; --col, ++colindex)
			{
				dmd->writePixel(col, row, GRAPHICS_NORMAL, 0);
				if(pxjmp_step > PATTERN_DISTANCE)
				{
					dmd->writePixel(col+PATTERN_COL_MAX*2, row, GRAPHICS_NORMAL, 0);
				}
			}
		}
		// shift the pixels by 1 bit
		++pxjmp_step;
		// start from the beginning
		// PATTERN_COL_MAX*2 : We need to add the offset bits in the matrix times the number of matrixes and the whole col number, representing the second pattern coming behind
		if(pxjmp_step == 64 + (PATTERN_COL_MAX * 2) + PATTERN_COL_MAX)
		{
			pxjmp_step = 0;
			step = 35;

			--cycle;
		}
	}
}

// Needs to be fixed
void PatternAnimator::draw_pattern_scrolling_pack(std::vector<std::vector<std::vector<int>>> pattern_pack, int ROW_START, int COL_START, int PATTERN_ROW_MAX, int PATTERN_COL_MAX, int pxjmp_step, double cycle)
{

	std::vector<int> tempcol =
	{
		{0},
		{0},
		{0},
		{0},
		{0},
		{0},
		{0}
	};

	float step = 35;
	while(cycle > 0)
	{
		for(int pattern=0; pattern<pattern_pack.size(); ++pattern)
		{
			for(int row=0; row<pattern_pack[pattern].size(); ++row)
			{
				pattern_pack[pattern][row].push_back(tempcol[row]);
			}
			// draw the pattern
			for(int row=ROW_START, rowindex=0; rowindex<pattern_pack[pattern].size(); ++row, ++rowindex)
			{
				for(int col=COL_START-pxjmp_step, colindex=0; colindex<pattern_pack[pattern][0].size(); --col, ++colindex)
				{
					dmd->writePixel(col, row, GRAPHICS_NORMAL, pattern_pack[pattern][rowindex][colindex]);
				}
			// dmd.writePixel(63-pxjmp_step+1, row, GRAPHICS_NORMAL, 0);
			}

			// delete the pattern
			for(int row=ROW_START, rowindex=0; rowindex<pattern_pack[pattern].size(); ++row, ++rowindex)
			{
				for(int col=COL_START-pxjmp_step, colindex=0; colindex<pattern_pack[pattern][0].size(); --col, ++colindex)
				{
					dmd->writePixel(col, row, GRAPHICS_NORMAL, 0);
				}
			}
		}
		

		delay(1.0f+ step);
		if(!(step < 12))
		{
			step = step-0.6f;
		}
		
		
		// shift the pixels by 1 bit
		pxjmp_step = pxjmp_step + 1;
		// start from the beginning
		if(pxjmp_step == 63)
		{
			pxjmp_step = 0;
			step = 35;

			--cycle;
		}
	}
}


void PatternAnimator::draw_pattern_tetris(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PANEL_LAST_COL, int pxjmp_step, int msdelay, double cycle)
{
	int PATTERN_ROW_MAX = pattern.size();
	int PATTERN_COL_MAX = pattern[0].size();

	float step = 35;
	int colindex = 0;
	int jmpstep_shifter = PANEL_LAST_COL;
	int offbit_counter = 0;
	while(cycle > 0)
	{
		// draw the col
		for(int row=ROW_START, col=COL_START-pxjmp_step, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
		{
			dmd->writePixel(col, row, GRAPHICS_NORMAL, pattern[rowindex][colindex]);
		}

		delay(2);

		// delete the col
		// if we reached the last col of the panel, skip deleting it
		if(pxjmp_step != (jmpstep_shifter-1))
		{
			for(int row=ROW_START, col=COL_START-pxjmp_step, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
			{
				dmd->writePixel(col, row, GRAPHICS_NORMAL, 0);
			}
		}
		// shift the pixels by 1 bit
		++pxjmp_step;
		// if we reached the end of the cols of the panel, we need to draw the next col
		if(pxjmp_step == jmpstep_shifter)
		{
			// reset to start from the beginning
			pxjmp_step = 0;
			// next col of the pattern
			++colindex;
			// we need to draw the next col 1 pixel behind the previous one
			--jmpstep_shifter;

			step = 35;
			if(colindex == PATTERN_COL_MAX) 
			{
				delay(3000);
				dmd->clearScreen(true);
				jmpstep_shifter = 55;
				colindex = 0;	
				--cycle;
			}
		}
	}
	
	

	// draw the pattern
	// for(int row=ROW_START, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
	// {
	// 	for(int col=COL_START-pxjmp_step, colindex=0; colindex<PATTERN_COL_MAX; --col, ++colindex)
	// 	{
	// 		dmd->writePixel(col, row, GRAPHICS_NORMAL, pattern[rowindex][colindex]);
	// 	}
	// // dmd.writePixel(63-pxjmp_step+1, row, GRAPHICS_NORMAL, 0);
	// }

}


void PatternAnimator::draw_pattern_static(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START)
{
	int PATTERN_ROW_MAX = pattern.size();
	int PATTERN_COL_MAX = pattern[0].size();
	// draw the pattern
	for(int row=ROW_START, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
	{
		for(int col=COL_START, colindex=0; colindex<PATTERN_COL_MAX; --col, ++colindex)
		{
			dmd->writePixel(col, row, GRAPHICS_NORMAL, pattern[rowindex][colindex]);
		}
		// dmd.writePixel(63-pxjmp_step+1, row, GRAPHICS_NORMAL, 0);
	}
}


void PatternAnimator::delete_pattern_static(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START)
{
	int PATTERN_ROW_MAX = pattern.size();
	int PATTERN_COL_MAX = pattern[0].size();
	// draw the pattern
	for(int row=ROW_START, rowindex=0; rowindex<PATTERN_ROW_MAX; ++row, ++rowindex)
	{
		for(int col=COL_START, colindex=0; colindex<PATTERN_COL_MAX; --col, ++colindex)
		{
			dmd->writePixel(col, row, GRAPHICS_NORMAL, 0);
		}
		// dmd.writePixel(63-pxjmp_step+1, row, GRAPHICS_NORMAL, 0);
	}
}

