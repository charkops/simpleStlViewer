#pragma once

#include <vector>
#include <utility>
#include <algorithm>


// Finds minimum and maximum element of vector
template <typename T>
std::pair<float, float> findMinMax(const std::vector<T> &vec) {
  auto maxIt = std::max_element(vec.begin(), vec.end());
  auto minIt = std::min_element(vec.begin(), vec.end());

  return std::make_pair(*minIt, *maxIt);
}

template <typename T>
void convertSingleNumber(T &number, float old_min, float old_max, float new_min, float new_max) {
  number = ((number - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
}

template <typename T>
void convertVectorToNDC(std::vector<T> &vec, float new_min = -0.5, float new_max = 0.5) {
  auto minMax = findMinMax(vec);
  auto min = minMax.first;
  auto max = minMax.second;

  for (auto & v : vec)
    convertSingleNumber(v, min, max, -0.5, 0.5);
};