/*
Complex Led Animation Simulation Program
*/

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <queue>
#include <set>
#include <thread>
#include <vector>
#include <iostream>
#include <functional>
#include <bitset>
#include <chrono>
#include <tuple>

using namespace std::literals;

std::vector<std::vector<int>> grid = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

std::vector<std::vector<int>> square_32 = {
  {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

// 64x64
std::vector<std::vector<int>> ball_64
  = {{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

// 8x64
std::vector<std::vector<int>> Battery
  = {{0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

struct CompareOrder
{
    bool ascending;
    explicit CompareOrder(bool asc = true) : ascending(asc) {}
    bool operator()(const std::tuple<const uint8_t*, int>& a, const std::tuple<const uint8_t*, int>& b) const
    {
        // Compare based on the order value
        if (ascending)
            return std::get<1>(a) < std::get<1>(b); // Ascending order
        else
            return std::get<1>(a) > std::get<1>(b); // Descending order
    }
};

class UniqueQueue
{
    std::priority_queue<std::tuple<const uint8_t*, int>, std::vector<std::tuple<const uint8_t*, int>>, CompareOrder>
      pqueue{};
    std::set<std::tuple<const uint8_t*, int>> proxy{};

  public:
    explicit UniqueQueue(bool ascending = true) : pqueue(CompareOrder(ascending)) {}
    void push(const std::tuple<const uint8_t*, int>& t)
    {
        if (this->proxy.insert(t).second)
        {
            this->pqueue.push(t);
        }
    }

    void pop()
    {
        this->proxy.erase(pqueue.top());
        this->pqueue.pop();
    }

    size_t size()
    {
        return this->pqueue.size();
    }

    bool empty()
    {
        return this->pqueue.empty();
    }

    std::tuple<const uint8_t*, int> top()
    {
        return this->pqueue.top();
    }
};

UniqueQueue slave_queue(false);
UniqueQueue proxy_queue(true);

uint8_t broadcastAddress_1[6] = {0x48, 0xE7, 0x29, 0xB7, 0xE1, 0xCC};
uint8_t broadcastAddress_2[6] = {0x78, 0x21, 0x84, 0xBB, 0x9F, 0x18};
uint8_t broadcastAddress_3[6] = {0x40, 0x22, 0xD8, 0x6E, 0x7F, 0xCC};

uint8_t broadcastAddress_4[6] = {0x40, 0x91, 0x51, 0xFD, 0x65, 0x84};
uint8_t broadcastAddress_5[6] = {0x08, 0xD1, 0xF9, 0xE8, 0x54, 0xF0};
uint8_t broadcastAddress_6[6] = {0xFC, 0xB4, 0x67, 0xC3, 0x4F, 0x44};
uint8_t broadcastAddress_7[6] = {0x08, 0xD1, 0xF9, 0xE9, 0xBC, 0x9C};

using struct_message_to_send = struct struct_message_to_send
{
    // Animation anim;
    char charArray[64];
    size_t bitSetStringSize;
    bool cmd = true;
    // int delay;
    // Flags slave_flag = Flags::None;
};

struct_message_to_send message_to_send;

using struct_message_to_receive = struct struct_message_to_receive
{
    // Animation anim;
    char charArray[64];
    size_t bitSetStringSize;
    bool cmd = true;
    // int delay;
    // Flags slave_flag = Flags::None;
};

struct_message_to_receive message_to_rcv;

void shift_matrix_down(std::vector<std::vector<int>>& matrix)
{
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Save the last row
    std::vector<int> lastRow = matrix[numRows - 1];

    // Shift each row down by one position
    for (int i = numRows - 1; i > 0; --i)
    {
        matrix[i] = matrix[i - 1];
    }

    // Place the last row at the top
    matrix[0] = lastRow;
}

void shift_matrix_up(std::vector<std::vector<int>>& matrix)
{
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Save the first row
    std::vector<int> firstRow = matrix[0];

    // Shift each row up by one position
    for (int i = 0; i < numRows - 1; ++i)
    {
        matrix[i] = matrix[i + 1];
    }

    // Place the first row at the bottom
    matrix[numRows - 1] = firstRow;
}

// Function to convert 2D vector to a bit string
std::string convertToBitString(const std::vector<std::vector<int>>& grid)
{
    std::string bitString;
    for (const auto& row : grid)
    {
        for (int cell : row)
        {
            bitString += (cell == 1) ? '1' : '0';
        }
    }
    return bitString;
}

// Function to compress the bit string into bit fields
std::string compressBitString(const std::string& bitString)
{
    std::string compressedString;
    for (size_t i = 0; i < bitString.size(); i += 8)
    {
        std::bitset<8> bits(bitString.substr(i, 8));
        compressedString += static_cast<char>(bits.to_ulong());
    }
    return compressedString;
}

// Function to convert bit string back into 2D vector
std::vector<std::vector<int>> convertFromBitString(const std::string& bitString, int numRows, int numCols)
{
    std::vector<std::vector<int>> grid(numRows, std::vector<int>(numCols));
    int index = 0;
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            grid[i][j] = (bitString[index++] == '1') ? 1 : 0;
        }
    }
    return grid;
}

// Function to decompress the compressed string back into bit string
std::string decompressBitString(const std::string& compressedString)
{
    std::string bitString;
    for (unsigned char c : compressedString)
    {
        std::bitset<8> bits(c);
        bitString += bits.to_string();
    }
    return bitString;
}

// Function to print binary representation of a character
std::string binaryString(unsigned char c)
{
    std::string result;
    for (int i = 7; i >= 0; --i)
    {
        result += ((c >> i) & 1) ? '1' : '0';
    }
    return result;
}

void shift_matrix_diagonal_once(std::vector<std::vector<int>>& grid)
{
    int numRows = grid.size();
    int numCols = grid[0].size();

    std::vector<std::vector<int>> temp(numRows, std::vector<int>(numCols, 0));

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            int new_i = (i + 1) % numRows;
            int new_j = (j + 1) % numCols;
            temp[new_i][new_j] = grid[i][j];
        }
    }
    grid = temp;
}

void shift_matrix_diagonal_decaying(std::vector<std::vector<int>>& grid)
{
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Shift each row down by one and each column to the right by one
    for (int i = numRows - 1; i >= 1; --i)
    {
        for (int j = numCols - 1; j >= 1; --j)
        {
            grid[i][j] = grid[i - 1][j - 1];
        }
    }

    // Clear the first row and first column
    for (int i = 0; i < numRows; ++i)
    {
        grid[i][0] = 0;
    }
    for (int j = 0; j < numCols; ++j)
    {
        grid[0][j] = 0;
    }
}

void shift_matrix_diagonal_decaying_upwards(std::vector<std::vector<int>>& grid)
{
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Shift each row up by one and each column to the right by one
    for (int i = 0; i < numRows - 1; ++i)
    {
        for (int j = numCols - 1; j >= 1; --j)
        {
            grid[i][j] = grid[i + 1][j - 1];
        }
    }

    // Clear the first column, except for the first row
    for (int i = 1; i < numRows; ++i)
    {
        grid[i][0] = 0;
    }

    // Clear the last row
    for (int j = 0; j < numCols; ++j)
    {
        grid[numRows - 1][j] = 0;
    }
}

void shift_matrix_right(std::vector<std::vector<int>>& grid)
{
    int size = grid.size();
    for (int i = 0; i < size; ++i)
    {
        int temp = grid[i][size - 1];
        for (int j = size - 1; j > 0; --j)
        {
            grid[i][j] = grid[i][j - 1];
        }
        grid[i][0] = temp;
    }
}

void prepare_next_matrix(std::vector<std::vector<int>>& matrix)
{
    std::string bitString = convertToBitString(matrix);
    std::string compressedString = compressBitString(bitString);

    size_t compressedSize = compressedString.size();
    // Serial.println(compressedSize);
    message_to_send.bitSetStringSize = compressedSize;
    for (size_t i = 0; i < compressedSize; ++i)
    {
        message_to_send.charArray[i] = compressedString[i];
    }
}

void prepare_and_shift_next_matrix(std::vector<std::vector<int>>& matrix,
                                   std::function<void(std::vector<std::vector<int>>&)> shifter,
                                   bool should_print = false)
{
    shifter(matrix);

    std::string bitString = convertToBitString(matrix);
    std::string compressedString = compressBitString(bitString);

    size_t compressedSize = compressedString.size();
    // Serial.println(compressedSize);
    message_to_send.bitSetStringSize = compressedSize;
    for (size_t i = 0; i < compressedSize; ++i)
    {
        message_to_send.charArray[i] = compressedString[i];
    }

    if (should_print)
    {
        std::cout << bitString.c_str() << "\n";
        std::cout << "Compressed String: "
                  << "\n";
        for (unsigned char c : message_to_send.charArray)
        {
            std::cout << binaryString(c).c_str() << "\n";
        }
    }
}

void setup()
{
    slave_queue.push(std::make_tuple(broadcastAddress_1, 1));
    slave_queue.push(std::make_tuple(broadcastAddress_2, 2));
    slave_queue.push(std::make_tuple(broadcastAddress_3, 3));
    slave_queue.push(std::make_tuple(broadcastAddress_4, 4));
    slave_queue.push(std::make_tuple(broadcastAddress_5, 5));
    slave_queue.push(std::make_tuple(broadcastAddress_6, 6));
    slave_queue.push(std::make_tuple(broadcastAddress_7, 7));
}

void printMatrix(const std::vector<std::vector<int>>& grid)
{
    const char* red = "\033[0;31m";
    const char* black = "\033[0;30m";
    const char* reset = "\033[0m";

    for (const auto& row : grid)
    {
        for (const auto& cell : row)
        {
            if (cell)
            {
                std::cout << red << "#" << reset;
            }
            else
            {
                std::cout << black << "." << reset;
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n\n\n";
}

void receive(const uint8_t* peer_addr, const uint8_t* data)
{
    std::vector<std::vector<int>> reconstructedGrid;
    std::string compressedString;

    memcpy(&message_to_rcv, data, sizeof(message_to_rcv));
    compressedString = std::string(message_to_rcv.charArray, 64);

    std::string decompressedString = decompressBitString(compressedString);
    reconstructedGrid = convertFromBitString(decompressedString, grid.size(), grid[0].size());
    printMatrix(reconstructedGrid);

    // std::cout << "\n\n\n";
}

void send(const uint8_t* peer_addr, const uint8_t* data)
{
    receive(peer_addr, data);
}

void multianim_diagonal_shift(std::vector<std::vector<int>> grid)
{
    constexpr auto ANIM_DELAY = std::chrono::milliseconds(500);
    constexpr auto SWITCH_DELAY = ANIM_DELAY * 4;
    size_t MAX_ROW = 8 * (slave_queue.size() + 1);
    int shape_length = 4;

    for (size_t i = 0; i < MAX_ROW; ++i)
    {
        // Animate Self

        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = grid.begin() + 8;
        for (auto it = grid.begin(); it != end_iterator; ++it)
        {
            self_anim_part.push_back(*it);
        }
        std::cout << "Master: "
                  << "\n";
        for (auto& row : self_anim_part)
        {
            for (auto& cell : row)
            {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n\n";
        int count = 2;
        // std::cout << "Queue Size: " << slave_queue.size() << "\n";

        // Animate Slaves
        while (!slave_queue.empty())
        {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = grid.begin() + (8 * count);
            for (auto it = grid.begin() + (8 * (count - 1)); it != end_iterator; ++it)
            {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            ++count;

            std::cout << "Slave " << std::get<1>(slave_queue.top()) << ": "
                      << "\n";
            send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send);

            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        while (!proxy_queue.empty())
        {
            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }
        shift_matrix_diagonal_decaying(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(50ms));
    }
}

void multianim_diagonal_shift_fold(std::vector<std::vector<int>> grid)
{
    constexpr auto ANIM_DELAY = std::chrono::milliseconds(500);
    constexpr auto SWITCH_DELAY = ANIM_DELAY * 4;
    constexpr size_t MAX_ROW = 64;
    bool flip = false;
    bool fold = true;
    int shape_length = 4;

    for (size_t i = 0; i < MAX_ROW - shape_length; ++i)
    {
        // Animate Self

        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = grid.begin() + 8;
        for (auto it = grid.begin(); it != end_iterator; ++it)
        {
            self_anim_part.push_back(*it);
        }
        std::cout << "Master: "
                  << "\n";
        for (auto& row : self_anim_part)
        {
            for (auto& cell : row)
            {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n\n";
        int count = 2;
        // std::cout << "Queue Size: " << slave_queue.size() << "\n";

        // Animate Slaves
        while (!slave_queue.empty())
        {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = grid.begin() + (8 * count);
            for (auto it = grid.begin() + (8 * (count - 1)); it != end_iterator; ++it)
            {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            ++count;

            std::cout << "Slave " << std::get<1>(slave_queue.top()) << ": "
                      << "\n";
            send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send);

            // if (fold && count == 5 && i == (MAX_ROW - shape_length)) {
            //     std::this_thread::sleep_for(5s);
            // }

            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        while (!proxy_queue.empty())
        {
            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }
        shift_matrix_diagonal_decaying(grid);
        std::this_thread::sleep_for(50ms);
    }

    while (!slave_queue.empty())
    {
        proxy_queue.push(slave_queue.top());
        slave_queue.pop();
    }

    std::this_thread::sleep_for(5s);

    // Fold to reverse direction
    for (size_t i = 0; i < MAX_ROW + 1; ++i)
    {
        int count = 8;
        while (!proxy_queue.empty())
        {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = grid.begin() + (8 * count);
            for (auto it = grid.begin() + (8 * (count - 1)); it != end_iterator; ++it)
            {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            --count;

            std::cout << "Slave " << std::get<1>(proxy_queue.top()) << ": "
                      << "\n";
            send(std::get<0>(proxy_queue.top()), (uint8_t*)&message_to_send);

            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }
        while (!slave_queue.empty())
        {
            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = grid.begin() + 8;
        for (auto it = grid.begin(); it != end_iterator; ++it)
        {
            self_anim_part.push_back(*it);
        }
        std::cout << "Master: "
                  << "\n";
        for (auto& row : self_anim_part)
        {
            for (auto& cell : row)
            {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n\n";
        shift_matrix_diagonal_decaying_upwards(grid);
        std::this_thread::sleep_for(50ms);
    }
}

//********************************

#include <cmath>
#include <iostream>
#include <random>

// class WavePattern
// {
//   private:
//     int verticalOffset;
//     double horizontalOffset;
//     double time;
//     std::mt19937 rng;
//     std::uniform_real_distribution<> dist;
//     bool horizontalShiftEnabled;
//     int horizontalShiftDirection;
//     double horizontalShiftExtent;

//   public:
//     std::vector<std::vector<int>> pattern;
//     WavePattern(bool enableHorizontalShift = false) : pattern(HEIGHT, std::vector<int>(WIDTH, 0)), verticalOffset(0),
//     horizontalOffset(0), time(0), rng(std::random_device{}()), dist(-0.05, 0.05),
//     horizontalShiftEnabled(enableHorizontalShift), horizontalShiftDirection(1), horizontalShiftExtent(0)
//     {
//         updatePattern();
//     }

//     void updatePattern()
//     {
//         // Clear the pattern
//         for (auto& row : pattern)
//         {
//             std::fill(row.begin(), row.end(), 0);
//         }

//         // Create the wave
//         double baseAmplitude = WIDTH / 8.0; // Reduced amplitude for shorter wave tops
//         double frequencyMod = 1.0 + 0.1 * std::sin(time * 0.1);

//         for (int y = 0; y < HEIGHT; ++y)
//         {
//             // Vary amplitude over time and add some randomness
//             double amplitude = baseAmplitude * (1 + 0.2 * std::sin(time * 0.05)) + dist(rng);

//             // Use a combination of sine waves for more frequent tops
//             double wave = std::sin((y + verticalOffset) * 0.4 * frequencyMod) + // Increased frequency
//                           0.3 * std::sin((y + verticalOffset) * 0.2 * frequencyMod + time * 0.1);

//             double x = (wave * amplitude) + (WIDTH * 0.6); // Moved base position more to the left

//             // Apply horizontal offset if enabled
//             if (horizontalShiftEnabled)
//             {
//                 x += horizontalOffset;
//             }

//             // Only draw the wave if it's within the grid
//             if (x >= 0 && x < WIDTH)
//             {
//                 int xInt = static_cast<int>(x);
//                 pattern[y][xInt] = 1;
//                 if (xInt > 0)
//                     pattern[y][xInt - 1] = 1;
//                 if (xInt < WIDTH - 1)
//                     pattern[y][xInt + 1] = 1;
//             }
//         }

//         time += 0.1;
//     }

//     void moveWaveVertical()
//     {
//         verticalOffset = (verticalOffset + 1) % HEIGHT;
//         updatePattern();
//     }

//     void moveWaveHorizontal()
//     {
//         if (horizontalShiftEnabled)
//         {
//             double minShift = WIDTH * 0.3; // 30% of width as minimum (more to the left)
//             double maxShift = WIDTH * 0.8; // 80% of width as maximum
//             double shiftRange = maxShift - minShift;

//             horizontalShiftExtent += 0.2 * horizontalShiftDirection; // Increased speed

//             if (horizontalShiftExtent > shiftRange || horizontalShiftExtent < 0)
//             {
//                 horizontalShiftDirection *= -1; // Reverse direction
//                 horizontalShiftExtent = std::max(0.0, std::min(horizontalShiftExtent, shiftRange));
//             }

//             horizontalOffset = minShift + horizontalShiftExtent - (WIDTH * 0.6); // Adjust for new base position

//             updatePattern();
//         }
//     }

//     void setHorizontalShiftEnabled(bool enabled)
//     {
//         horizontalShiftEnabled = enabled;
//     }

//     void print() const
//     {
//         for (const auto& row : pattern)
//         {
//             for (int cell : row)
//             {
//                 std::cout << (cell ? "1" : ".");
//             }
//             std::cout << std::endl;
//         }
//         std::cout << std::endl;
//     }
// };

// Define M_PI if it's not already defined
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

  public:
    std::vector<std::vector<int>> pattern;

    WavePattern(bool enableHorizontalShift = false)
        : pattern(HEIGHT, std::vector<int>(WIDTH, 0)), verticalOffset(0), horizontalOffset(0), time(0),
          rng(std::random_device{}()), dist(-0.05, 0.05), horizontalShiftEnabled(enableHorizontalShift),
          horizontalShiftDirection(1), horizontalShiftExtent(0)
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
        double baseAmplitude = WIDTH / 4.0;
        double frequencyMod = 1.0 + 0.1 * std::sin(time * 0.1);

        for (int y = 0; y < HEIGHT; ++y)
        {
            // Use a sine wave with varying frequency to create approximately two max points
            double wave = std::sin((y + verticalOffset) * (2 * M_PI / HEIGHT) * frequencyMod);

            // Add some variation to the wave
            wave += 0.2 * std::sin((y + verticalOffset) * (4 * M_PI / HEIGHT) + time);

            double amplitude = baseAmplitude * (1 + 0.2 * std::sin(time * 0.05)) + dist(rng);
            double x = (wave * amplitude) + (WIDTH * 0.5);

            // Apply horizontal offset if enabled
            if (horizontalShiftEnabled)
            {
                x += horizontalOffset;
            }

            // Fill everything to the left of the wave point
            int xInt = static_cast<int>(x);
            for (int fillX = 0; fillX <= xInt && fillX < WIDTH; ++fillX)
            {
                pattern[y][fillX] = 1;
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
            double minShift = -WIDTH / 6.0;
            double maxShift = WIDTH / 6.0;
            double shiftRange = maxShift - minShift;

            horizontalShiftExtent += 0.1 * horizontalShiftDirection;

            if (horizontalShiftExtent > shiftRange || horizontalShiftExtent < 0)
            {
                horizontalShiftDirection *= -1;
                horizontalShiftExtent = std::max(0.0, std::min(horizontalShiftExtent, shiftRange));
            }

            horizontalOffset = minShift + horizontalShiftExtent;

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

void multianim_wave()
{
    // multianim_diagonal_shift(ball_64);

    // Create two wave patterns, one with horizontal shift and one without
    WavePattern waveWithShift(true);
    // WavePattern waveWithoutShift(false);

    constexpr auto ANIM_DELAY = std::chrono::milliseconds(500);

    // std::vector<std::vector<int>> grid = waveWithShift.pattern;

    // Animation loop
    for (int i = 0; i < 1000; ++i)
    {
        // Animate Self

        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = waveWithShift.pattern.begin() + 8;
        for (auto it = waveWithShift.pattern.begin(); it != end_iterator; ++it)
        {
            self_anim_part.push_back(*it);
        }
        std::cout << "Master: "
                  << "\n";
        printMatrix(self_anim_part);
        std::cout << "\n\n\n";

        int count = 2;

        while (!slave_queue.empty())
        {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = waveWithShift.pattern.begin() + (8 * count);
            for (auto it = waveWithShift.pattern.begin() + (8 * (count - 1)); it != end_iterator; ++it)
            {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            ++count;

            std::cout << "Slave " << std::get<1>(slave_queue.top()) << ": "
                      << "\n";
            send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send);

            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        while (!proxy_queue.empty())
        {
            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }

        // std::cout << "Frame " << i << " - Without Horizontal Shift:" << std::endl;
        // waveWithoutShift.print();

        waveWithShift.moveWaveVertical();
        // waveWithoutShift.moveWaveVertical();

        // Move the wave horizontally every frame for the shifting version
        waveWithShift.moveWaveHorizontal();

        std::this_thread::sleep_for(std::chrono::milliseconds(ANIM_DELAY));

        // In a real-time system, you'd add a delay here
    }
}

//********************************

/////////////////////////////////////////
//************** BATTERY *******************
/////////////////////////////////////////

// Function to add a battery fill to the grid
void addBatteryFill(std::vector<std::vector<int>>& grid, int startCol, int width = 3, int height = 8)
{
    if (startCol + width > grid[0].size())
    {
        throw std::out_of_range("Battery fill exceeds grid width");
    }

    for (int row = 0; row < height && row < grid.size(); ++row)
    {
        for (int col = startCol; col < startCol + width; ++col)
        {
            grid[row][col] = 1;
        }
    }
}

void multianim_battery()
{
    constexpr auto ANIM_DELAY = std::chrono::milliseconds(100);
    constexpr auto SWITCH_DELAY = ANIM_DELAY * 4;
    size_t MAX_BATTERY = 12;
    int shape_length = 4;
    const int HEIGHT = 8;
    const int WIDTH = 64;

    std::vector<std::vector<int>> blink(HEIGHT, std::vector<int>(WIDTH, 0));
    std::vector<std::vector<int>> battery = Battery;
    // std::vector<std::vector<int>> tempBattery(HEIGHT, std::vector<int>(WIDTH, 0));

    for (size_t i = 0; i <= MAX_BATTERY; ++i)
    {
        // Animate Self

        // Show - Blink - Show - Blink - Show - Blink,
        // Blink - Show - Blink - Show - Blink - Show
        // Then we increment Battery
        for (int i = 0; i < 3; ++i)
        {
            std::cout << "Master: "
                      << "\n";

            printMatrix(blink);
            std::cout << "\n\n\n";
            int count = 2;
            // std::cout << "Queue Size: " << slave_queue.size() << "\n";

            // Animate Slaves
            while (!slave_queue.empty())
            {
                prepare_next_matrix(blink);

                ++count;

                std::cout << "Slave " << std::get<1>(slave_queue.top()) << ": "
                          << "\n";
                send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send);

                proxy_queue.push(slave_queue.top());
                slave_queue.pop();
            }
            while (!proxy_queue.empty())
            {
                slave_queue.push(proxy_queue.top());
                proxy_queue.pop();
            }
            // shift_matrix_diagonal_decaying(grid);
            std::this_thread::sleep_for(ANIM_DELAY);

            // BLINK

            std::cout << "Master: "
                      << "\n";

            printMatrix(battery);
            std::cout << "\n\n\n";
            count = 2;

            // Animate Slaves
            while (!slave_queue.empty())
            {
                prepare_next_matrix(battery);

                ++count;

                std::cout << "Slave " << std::get<1>(slave_queue.top()) << ": "
                          << "\n";
                send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send);

                proxy_queue.push(slave_queue.top());
                slave_queue.pop();
            }
            while (!proxy_queue.empty())
            {
                slave_queue.push(proxy_queue.top());
                proxy_queue.pop();
            }
            // shift_matrix_diagonal_decaying(grid);
            std::this_thread::sleep_for(ANIM_DELAY);
        }
        // TRIPLE BLINK ENDED
        // TIME TO SHIFT THE BATTERY SIDEWAYS
        if (i < MAX_BATTERY) // IF we are on the last fill, we have to exit, to avoid going out
        {
            blink = battery; // will be used to act as a blinker for the next incremented battery
            addBatteryFill(battery, 6 + (i * 5));
        }
    }
}

class PatternShifter
{
  private:
    const std::vector<std::vector<int>>& pattern;
    int offsetX;
    int offsetY;

  public:
    PatternShifter(const std::vector<std::vector<int>>& grid) : pattern(grid), offsetX(0), offsetY(0) {}

    void shiftLeft()
    {
        offsetX = std::min(offsetX + 1, static_cast<int>(pattern[0].size()));
    }

    void shiftRight()
    {
        offsetX = std::max(offsetX - 1, -static_cast<int>(pattern[0].size()));
    }

    void shiftUp()
    {
        offsetY = std::max(offsetY - 1, -static_cast<int>(pattern.size()));
    }

    void shiftDown()
    {
        offsetY = std::min(offsetY + 1, static_cast<int>(pattern.size()));
    }

    std::vector<std::vector<int>> getDisplayFrame(int rows, int cols) const
    {
        std::vector<std::vector<int>> frame(rows, std::vector<int>(cols, 0));
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int patternRow = i - offsetY;
                int patternCol = j + offsetX;
                if (patternRow >= 0 && patternRow < pattern.size() && patternCol >= 0 && patternCol < pattern[0].size())
                {
                    frame[i][j] = pattern[patternRow][patternCol];
                }
            }
        }
        return frame;
    }
};

int main()
{
    std::vector<std::vector<int>> pattern = {
      {1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
      {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
      {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0},
      {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
      {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
      {1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
    };

    PatternShifter shifter(pattern);
    int rows = 7, cols = 35;

    shifter.shiftDown();
    printMatrix(shifter.getDisplayFrame(rows, cols));
    shifter.shiftDown();
    printMatrix(shifter.getDisplayFrame(rows, cols));
    shifter.shiftDown();
    printMatrix(shifter.getDisplayFrame(rows, cols));
    shifter.shiftDown();
    printMatrix(shifter.getDisplayFrame(rows, cols));
    shifter.shiftDown();
    printMatrix(shifter.getDisplayFrame(rows, cols));
    shifter.shiftDown();
    printMatrix(shifter.getDisplayFrame(rows, cols));
    shifter.shiftDown();

    return 0;
}