#include <vector>
#include <cmath>
#include <iostream>
#include <random>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int WIDTH = 64;
const int HEIGHT = 64;

class WavePattern
{
  private:
    int verticalOffset;
    double horizontalOffset;
    double time;
    std::mt19937 rng;
    std::uniform_real_distribution<> dist;
    bool horizontalShiftEnabled;
    int horizontalShiftDirection;
    double horizontalShiftExtent;
    double minX;
    double maxX;
    bool filled;
    int lineThickness;

  public:
    std::vector<std::vector<int>> pattern;

    WavePattern(double minXPercent = 0.10, double maxXPercent = 0.40, bool enableHorizontalShift = false,
                bool isFilled = true, int thickness = 3)
        : pattern(HEIGHT, std::vector<int>(WIDTH, 0)), verticalOffset(0), horizontalOffset(0), time(0),
          rng(std::random_device{}()), dist(-0.5, 0.5), horizontalShiftEnabled(enableHorizontalShift),
          horizontalShiftDirection(1), horizontalShiftExtent(0), minX(WIDTH * minXPercent), maxX(WIDTH * maxXPercent),
          filled(isFilled), lineThickness(thickness)
    {
        updatePattern();
    }

    void updatePattern()
    {
        // Clear the pattern
        for (auto& row : pattern)
        {
            std::fill(row.begin(), row.end(), 0);
        }

        double range = maxX - minX;
        double baseAmplitude = range * 0.4; // Use 40% of the range as amplitude for thinner waves
        double frequencyMod = 1.0 + 0.2 * std::sin(time * 0.15);

        for (int y = 0; y < HEIGHT; ++y)
        {
            // Use multiple sine waves with different frequencies for more variation
            double wave = std::sin((y + verticalOffset) * (4 * M_PI / HEIGHT) * frequencyMod);
            wave += 0.5 * std::sin((y + verticalOffset) * (7 * M_PI / HEIGHT) + time * 1.1);
            wave += 0.3 * std::sin((y + verticalOffset) * (11 * M_PI / HEIGHT) - time * 0.7);

            // Normalize the wave to [-1, 1] range
            wave /= 1.8;

            double amplitude = baseAmplitude * (0.8 + 0.4 * std::sin(time * 0.07)) + dist(rng);
            double x = (wave * amplitude) + (minX + range * 0.5); // Center at midpoint of range

            // Apply horizontal offset if enabled
            if (horizontalShiftEnabled)
            {
                x += horizontalOffset;
            }

            // Clamp x to the desired range
            x = std::max(minX, std::min(x, maxX));

            int xInt = static_cast<int>(x);

            if (filled)
            {
                // Fill everything to the left of the wave point
                for (int fillX = 0; fillX <= xInt && fillX < WIDTH; ++fillX)
                {
                    pattern[y][fillX] = 1;
                }
            }
            else
            {
                // Draw a thick line for the wave
                for (int t = -lineThickness / 2; t <= lineThickness / 2; ++t)
                {
                    int drawX = xInt + t;
                    if (drawX >= 0 && drawX < WIDTH)
                    {
                        pattern[y][drawX] = 1;
                    }
                }
            }
        }

        time += 0.05;
    }

    void moveWaveVertical()
    {
        verticalOffset = (verticalOffset + 1) % HEIGHT;
        updatePattern();
    }

    void moveWaveHorizontal()
    {
        if (horizontalShiftEnabled)
        {
            double shiftRange = maxX - minX;

            horizontalShiftExtent += 0.3 * horizontalShiftDirection;

            if (horizontalShiftExtent > shiftRange || horizontalShiftExtent < 0)
            {
                horizontalShiftDirection *= -1;
                horizontalShiftExtent = std::max(0.0, std::min(horizontalShiftExtent, shiftRange));
            }

            horizontalOffset = horizontalShiftExtent - (shiftRange * 0.5); // Center the shift

            updatePattern();
        }
    }

    void setHorizontalShiftEnabled(bool enabled)
    {
        horizontalShiftEnabled = enabled;
    }

    void setFilled(bool isFilled)
    {
        filled = isFilled;
        updatePattern();
    }

    void setRange(double minXPercent, double maxXPercent)
    {
        minX = WIDTH * minXPercent;
        maxX = WIDTH * maxXPercent;
        updatePattern();
    }

    void setLineThickness(int thickness)
    {
        lineThickness = thickness;
        updatePattern();
    }

    void print() const
    {
        for (const auto& row : pattern)
        {
            for (int cell : row)
            {
                std::cout << (cell ? "1" : ".");
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int main()
{
    // Create four wave patterns with different configurations
    // WavePattern waveFilled(0.10, 0.40, true, true);
    WavePattern waveUnfilled(0.10, 0.40, true, false, 6); // Thickness of 3
    // WavePattern waveNarrow(0.20, 0.30, false, true);
    // WavePattern waveWide(0.05, 0.45, false, false, 5); // Thickness of 5

    // Animation loop
    for (int i = 0; i < 1000; ++i)
    {
        // std::cout << "Frame " << i << " - Filled Wave (10-40%):" << std::endl;
        // waveFilled.print();

        std::cout << "Frame " << i << " - Unfilled Wave (10-40%, thickness 3):" << std::endl;
        waveUnfilled.print();

        // std::cout << "Frame " << i << " - Narrow Filled Wave (20-30%):" << std::endl;
        // waveNarrow.print();

        // std::cout << "Frame " << i << " - Wide Unfilled Wave (5-45%, thickness 5):" << std::endl;
        // waveWide.print();

        // waveFilled.moveWaveVertical();
        // waveFilled.moveWaveHorizontal();

        waveUnfilled.moveWaveVertical();
        waveUnfilled.moveWaveHorizontal();

        // waveNarrow.moveWaveVertical();

        // waveWide.moveWaveVertical();

        // In a real-time system, you'd add a delay here
    }

    return 0;
}