

#include "p10_animations_kilicarslan.h"
#include <DMD32.h>  

// Pattern definitions

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
	{0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,1,0,0,0}
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
//7x11
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
// 7x11
std::vector<std::vector<int>> PatternAnimator::spaceship =
{
	{0,0,0,1,0,1,0,0,0,0,0},
	{1,0,0,1,0,0,1,0,1,0,0},
	{0,1,0,0,1,0,0,1,0,1,0},
	{1,1,1,1,0,0,0,0,1,1,1},
	{0,1,0,0,1,0,0,1,0,1,0},
	{1,0,0,1,0,0,1,0,1,0,0},
	{0,0,0,1,0,1,0,0,0,0,0}
};
// 7x11
std::vector<std::vector<int>> PatternAnimator::claw =
{
	{0,0,0,0,0,0,0,1,1,0,0},
	{0,0,0,0,0,0,1,0,0,1,0},
	{0,0,0,0,0,1,0,0,0,0,1},
	{1,1,1,1,1,0,1,1,0,0,1},
	{0,0,0,0,0,1,0,0,1,0,0},
	{0,0,0,0,0,0,1,0,0,1,0},
	{0,0,0,0,0,1,0,0,1,0,0}
};
// 7x11
std::vector<std::vector<int>> PatternAnimator::stripe =
{
	{1,0,0,1,0,0,1,0,0,1,0},
	{0,1,0,0,1,0,0,1,0,0,1},
	{0,0,1,0,0,1,0,0,1,0,0},
	{1,0,0,1,0,0,1,0,0,1,0},
	{0,1,0,0,1,0,0,1,0,0,1},
	{0,0,1,0,0,1,0,0,1,0,0},
	{0,0,0,1,0,0,1,0,0,1,0}
};
// 7x7
std::vector<std::vector<int>> PatternAnimator::sword =
{
	{0,0,0,0,0,0,1},
	{0,0,0,0,0,1,0},
	{1,0,0,0,1,0,0},
	{0,1,0,1,0,0,0},
	{0,1,1,0,0,0,0},
	{0,1,1,1,0,0,0},
	{1,0,0,0,1,0,0}
};
// 7x7
std::vector<std::vector<int>> PatternAnimator::bomb =
{
	{0,0,0,0,0,1,0},
	{0,0,0,0,1,0,1},
	{0,0,0,1,0,0,0},
	{0,1,1,0,0,0,1},
	{1,1,1,1,0,0,0},
	{1,1,1,1,0,0,0},
	{0,1,1,0,0,0,0}
};
// 7x7
std::vector<std::vector<int>> PatternAnimator::robot =
{
	{0,0,1,0,1,0,0},
	{0,1,0,0,0,1,0},
	{0,0,1,1,1,0,0},
	{0,0,0,1,0,0,0},
	{0,1,1,1,1,1,0},
	{1,0,0,1,0,0,1},
	{0,0,1,1,1,0,0}
};
// 7x7
std::vector<std::vector<int>> PatternAnimator::excmark_45 =
{
	{0,0,0,0,0,1,1},
	{0,0,0,0,0,1,1},
	{0,0,0,1,0,0,0},
	{0,0,1,1,1,0,0},
	{0,1,1,1,0,0,0},
	{1,1,1,0,0,0,0},
	{1,1,0,0,0,0,0}
};
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

std::vector<std::vector<std::vector<int>>> PatternAnimator::pattern_pack;


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


void PatternAnimator::rotate_matrix_90(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    // Transpose matrix
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
    // Reverse each row
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n/2; j++) {
            std::swap(matrix[i][j], matrix[i][n-1-j]);
        }
    }
}


void PatternAnimator::draw_pattern_scrolling(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, float delaystep, double cycle)
{
	int PATTERN_ROW_MAX = pattern.size();
	int PATTERN_COL_MAX = pattern[0].size();
	COL_START += PATTERN_COL_MAX;
	float step = delaystep;
	int pxjmp_step = 0;
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


void PatternAnimator::draw_pattern_scrolling_rotating(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, float delaystep, double cycle)
{
	int PATTERN_ROW_MAX = pattern.size();
	int PATTERN_COL_MAX = pattern[0].size();
	COL_START += PATTERN_COL_MAX;
	float step = delaystep;
	int pxjmp_step = 0;
	int frame_counter = 0;
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
		// rotate the pattern every 10th frame, pxjmp_step increments by 1 so every 2 steps, we increment by 1 and rotate when we reach 5
		if(pxjmp_step % 2 == 0)
		{
			++frame_counter;
			if(frame_counter == 5)
			{
				rotate_matrix_90(pattern);
				frame_counter = 0;
			}
			
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


void PatternAnimator::draw_pattern_scrolling_series(std::vector<std::vector<std::vector<int>>> pattern_pack, int ROW_START, int COL_START, int PATTERN_DISTANCE, float delaystep, double cycle)
{
	// int PATTERN_ROW_MAX = pattern_pack[0].size();
	int PATTERN_COL_MAX = pattern_pack[0][0].size();
	COL_START += PATTERN_COL_MAX;
	float step = delaystep;
	int pxjmp_step = 0;
	
	while(cycle > 0)
	{
		for(int patternindex=0, counter=0; patternindex < pattern_pack.size(); ++patternindex, counter+=(PATTERN_DISTANCE+PATTERN_COL_MAX))
		{
			// draw the pattern
			for(int row=ROW_START, rowindex=0; rowindex < pattern_pack[patternindex].size(); ++row, ++rowindex)
			{
				for(int col=COL_START-pxjmp_step, colindex=0; colindex < pattern_pack[patternindex][rowindex].size(); --col, ++colindex)
				{
					dmd->writePixel(col+counter, row, GRAPHICS_NORMAL, pattern_pack[patternindex][rowindex][colindex]);
				}
			}
		}

		delay(1.0f+ delaystep);
		if(!(delaystep < 12))
		{
			delaystep = delaystep-0.6f;
		}
		
		for(int patternindex=0, counter=0; patternindex < pattern_pack.size(); ++patternindex, counter+=(PATTERN_DISTANCE+PATTERN_COL_MAX))
		{
			// delete the pattern
			for(int row=ROW_START, rowindex=0; rowindex < pattern_pack[patternindex].size(); ++row, ++rowindex)
			{
				for(int col=COL_START-pxjmp_step, colindex=0; colindex < pattern_pack[patternindex][rowindex].size(); --col, ++colindex)
				{
					dmd->writePixel(col+counter, row, GRAPHICS_NORMAL, 0);
				}
			}
		}
		
		// shift the pixels by 1 bit
		++pxjmp_step;
		// start from the beginning
		// PATTERN_COL_MAX*pattern_pack.size() : We need to add the offset bits in the matrix times the number of matrixes and the whole col number, representing the second pattern coming behind
		if(pxjmp_step == 64 + (PATTERN_COL_MAX * pattern_pack.size() * 2) + PATTERN_COL_MAX)
		{
			pxjmp_step = 0;
			delaystep = step;

			--cycle;
		}
	}
}


void PatternAnimator::draw_pattern_tetris(std::vector<std::vector<int>> pattern, int ROW_START, int COL_START, int PANEL_LAST_COL, int msdelay, double cycle)
{
	int PATTERN_ROW_MAX = pattern.size();
	int PATTERN_COL_MAX = pattern[0].size();

	float step = 35;
	int pxjmp_step = 0;
	int colindex = 0;
	int jmpstep_shifter = PANEL_LAST_COL;
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
}


