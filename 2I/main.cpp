#include <iostream>
#include <queue>
#include <string>
#include <vector>

const int kMask = 0xFF;

template <typename T>
void ReadArray(std::vector<T>& array) {
  for (size_t i = 0; i < array.size(); ++i) {
    std::cin >> array[i];
  }
}

template <typename T>
void PrintArray(const std::vector<T>& array, char format) {
  for (size_t i = 0; i < array.size(); ++i) {
    std::cout << array[i] << format;
  }
}

template <typename T>
int GetLSD(T& num, int digit, const int kCountBytes) {
  return (num >> (kCountBytes * digit)) & kMask;
}

template <typename T>
void LSDSort(std::vector<T>& array) {
  std::vector<T> temp(array.size());
  const int kCountBytes = sizeof(T);

  for (int digit = 0; digit < kCountBytes; ++digit) {
    std::vector<int> count(kMask + 1);
    for (size_t i = 0; i < array.size(); ++i) {
      ++count[GetLSD(array[i], digit, kCountBytes)];
    }
    for (int i = 1; i <= kMask; ++i) {
      count[i] += count[i - 1];
    }
    for (int i = static_cast<int>(array.size()) - 1; i >= 0; --i) {
      temp[count[GetLSD(array[i], digit, kCountBytes)] - 1] = array[i];
      --count[GetLSD(array[i], digit, kCountBytes)];
    }

    array = temp;
  }
}

int main() {
  int num;
  std::cin >> num;
  std::vector<unsigned long long> array(num);
  ReadArray(array);
  LSDSort(array);
  PrintArray(array, '\n');
  return 0;
}