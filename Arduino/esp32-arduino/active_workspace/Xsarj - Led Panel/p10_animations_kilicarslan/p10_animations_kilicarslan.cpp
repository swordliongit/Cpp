

#include "p10_animations_kilicarslan.h"
#include <DMD32.h>  


void PatternAnimator::draw_blinking_pattern(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PATTERN_ROW_MAX, int PATTERN_COL_MAX, int msdelay, int cycle)
{
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


void PatternAnimator::draw_scrolling_pattern(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PATTERN_ROW_MAX, int PATTERN_COL_MAX, int pxjmp_step, int cycle)
{
	float step = 35;
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
			}
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