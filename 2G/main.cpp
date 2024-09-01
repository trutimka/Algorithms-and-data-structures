#include <iostream>
#include <queue>
#include <string>
#include <vector>

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
int GetPivot(const std::vector<T>& array, int left, int right) {
  int mid = (left + right) / 2;
  if ((array[left] <= array[mid] && array[mid] <= array[right]) ||
      (array[right] <= array[mid] && array[mid] <= array[left])) {
    return array[mid];
  }
  if ((array[mid] <= array[left] && array[left] <= array[right]) ||
      (array[right] <= array[left] && array[left] <= array[mid])) {
    return array[left];
  }
  return array[right];
}

template <typename T>
int Partition(std::vector<T>& array, int left, int right) {
  int pivot = GetPivot(array, left, right);
  int lef = left;
  int rig = right;
  while (lef <= rig) {
    while (array[lef] < pivot) {
      ++lef;
    }
    while (array[rig] > pivot) {
      --rig;
    }
    if (lef >= rig) {
      break;
    }
    std::swap(array[lef], array[rig]);
    --rig;
    ++lef;
  }
  return rig;
}

template <typename T>
void QuickSort(std::vector<T>& array, int left, int right) {
  if (right == left) {
    return;
  }
  int part = Partition(array, left, right);
  QuickSort(array, left, part);
  QuickSort(array, part + 1, right);
}

int main() {
  int num;
  std::cin >> num;
  std::vector<int> array(num);
  ReadArray(array);
  QuickSort(array, 0, num - 1);
  PrintArray(array, ' ');
  return 0;
}