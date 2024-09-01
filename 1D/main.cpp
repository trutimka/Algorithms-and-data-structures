#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
std::vector<T> ReadVector(const size_t& size) {
  std::vector<T> array(size);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  return array;
}

template <typename T>
void PrintVector(const std::vector<T>& array, const char kSym) {
  for (const auto& item : array) {
    std::cout << item << kSym;
  }
  std::cout << '\n';
}

template <typename T>
bool Check(const std::vector<T>& array, size_t dist, size_t coun) {
  size_t count = 1;
  size_t lastcord = array[0];
  for (size_t i = 1; i < array.size(); ++i) {
    if (array[i] - lastcord >= dist) {
      ++count;
      lastcord = array[i];
    }
  }
  return count >= coun;
}

template <typename T>
size_t FindAnswer(const std::vector<T>& array, size_t count) {
  size_t dist = (array[array.size() - 1] - array[0]) / 2;
  size_t left = 0;
  size_t right = array[array.size() - 1];
  while (right - left > 1) {
    if (Check(array, dist, count)) {
      left = dist;
    } else {
      right = dist;
    }
    dist = left + (right - left) / 2;
  }
  dist = left + (right - left) / 2;
  return dist;
}

int main() {
  size_t num;
  size_t count;
  std::cin >> num >> count;
  std::vector<int> arr = ReadVector<int>(num);
  std::cout << FindAnswer(arr, count);
  return 0;
}