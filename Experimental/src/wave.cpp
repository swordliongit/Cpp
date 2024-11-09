#include <vector>
#include <cmath>
#include <iostream>
#include <random>

const int WIDTH = 64;
const int HEIGHT = 64;

class WavePattern
{
  private:
    std::vector<std::vector<int>> pattern;
    int verticalOffset;
    double horizontalOffset;
    double time;
    std::mt19937 rng;
    std::uniform_real_distribution<> dist;
    bool horizontalShiftEnabled;
    int horizontalShiftDirection;
    double horizontalShiftExtent;

  public:
    WavePattern(bool enableHorizontalShift = false) : pattern(HEIGHT, std::vector<int>(WIDTH, 0)), verticalOffset(0), horizontalOffset(0), time(0), rng(std::random_device{}()), dist(-0.05, 0.05), horizontalShiftEnabled(enableHorizontalShift), horizontalShiftDirection(1), horizontalShiftExtent(0)
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

        // Create the wave
        double baseAmplitude = WIDTH / 8.0; // Reduced amplitude for shorter wave tops
        double frequencyMod = 1.0 + 0.1 * std::sin(time * 0.1);

        for (int y = 0; y < HEIGHT; ++y)
        {
            // Vary amplitude over time and add some randomness
            double amplitude = baseAmplitude * (1 + 0.2 * std::sin(time * 0.05)) + dist(rng);

            // Use a combination of sine waves for more frequent tops
            double wave = std::sin((y + verticalOffset) * 0.4 * frequencyMod) + // Increased frequency
                          0.3 * std::sin((y + verticalOffset) * 0.2 * frequencyMod + time * 0.1);

            double x = (wave * amplitude) + (WIDTH * 0.6); // Moved base position more to the left

            // Apply horizontal offset if enabled
            if (horizontalShiftEnabled)
            {
                x += horizontalOffset;
            }

            // Only draw the wave if it's within the grid
            if (x >= 0 && x < WIDTH)
            {
                int xInt = static_cast<int>(x);
                pattern[y][xInt] = 1;
                if (xInt > 0)
                    pattern[y][xInt - 1] = 1;
                if (xInt < WIDTH - 1)
                    pattern[y][xInt + 1] = 1;
            }
        }

        time += 0.1;
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
            double minShift = WIDTH * 0.3; // 30% of width as minimum (more to the left)
            double maxShift = WIDTH * 0.8; // 80% of width as maximum
            double shiftRange = maxShift - minShift;

            horizontalShiftExtent += 0.2 * horizontalShiftDirection; // Increased speed

            if (horizontalShiftExtent > shiftRange || horizontalShiftExtent < 0)
            {
                horizontalShiftDirection *= -1; // Reverse direction
                horizontalShiftExtent = std::max(0.0, std::min(horizontalShiftExtent, shiftRange));
            }

            horizontalOffset = minShift + horizontalShiftExtent - (WIDTH * 0.6); // Adjust for new base position

            updatePattern();
        }
    }

    void setHorizontalShiftEnabled(bool enabled)
    {
        horizontalShiftEnabled = enabled;
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
    // Create two wave patterns, one with horizontal shift and one without
    WavePattern waveWithShift(true);
    WavePattern waveWithoutShift(false);

    // Animation loop
    for (int i = 0; i < 1000; ++i)
    {
        std::cout << "Frame " << i << " - With Horizontal Shift:" << std::endl;
        waveWithShift.print();

        // std::cout << "Frame " << i << " - Without Horizontal Shift:" << std::endl;
        // waveWithoutShift.print();

        waveWithShift.moveWaveVertical();
        // waveWithoutShift.moveWaveVertical();

        // Move the wave horizontally every frame for the shifting version
        waveWithShift.moveWaveHorizontal();

        // In a real-time system, you'd add a delay here
    }

    return 0;
}