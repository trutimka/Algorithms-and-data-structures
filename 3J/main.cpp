#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
void ReadBlock(std::vector<T>& block);

template <typename T>
void ReadBlocks(std::vector<std::vector<T>>& arrays);

template <typename T>
void PrintResult(const std::vector<T>& array);

template <typename T>
void MergeTwoVectors(std::vector<T>& result, std::vector<T>& left,
                     std::vector<T>& right);

template <typename T>
void MergeSortVectors(const std::vector<std::vector<T>>& arrays,
                      std::vector<T>& result, size_t left, size_t right);

int main() {
  size_t count = 0;
  std::cin >> count;

  std::vector<std::vector<int>> arrays(count);
  ReadBlocks(arrays);

  std::vector<int> result;
  MergeSortVectors(arrays, result, 0, count - 1);

  PrintResult(result);

  return 0;
}

template <typename T>
void ReadBlock(std::vector<T>& block) {
  size_t count = 0;
  std::cin >> count;
  block.resize(count);
  for (size_t i = 0; i < count; ++i) {
    std::cin >> block[i];
  }
}

template <typename T>
void ReadBlocks(std::vector<std::vector<T>>& arrays) {
  for (size_t i = 0; i < arrays.size(); ++i) {
    ReadBlock(arrays[i]);
  }
}

template <typename T>
void PrintResult(const std::vector<T>& array) {
  for (auto num : array) {
    std::cout << num << ' ';
  }
}

template <typename T>
void MergeTwoVectors(std::vector<T>& result, std::vector<T>& left,
                     std::vector<T>& right) {
  size_t left_index = 0;
  size_t right_index = 0;
  while (left_index < left.size() && right_index < right.size()) {
    if (left[left_index] < right[right_index]) {
      result.push_back(left[left_index]);
      ++left_index;
    } else {
      result.push_back(right[right_index]);
      ++right_index;
    }
  }

  while (left_index < left.size()) {
    result.push_back(left[left_index]);
    ++left_index;
  }

  while (right_index < right.size()) {
    result.push_back(right[right_index]);
    ++right_index;
  }
}

template <typename T>
void MergeSortVectors(const std::vector<std::vector<T>>& arrays,
                      std::vector<T>& result, size_t left, size_t right) {
  if (left == right) {
    result = arrays[left];
    return;
  }
  size_t middle = (left + right) / 2;
  std::vector<int> result_left;
  std::vector<int> result_right;
  MergeSortVectors(arrays, result_left, left, middle);
  MergeSortVectors(arrays, result_right, middle + 1, right);
  MergeTwoVectors(result, result_left, result_right);
}