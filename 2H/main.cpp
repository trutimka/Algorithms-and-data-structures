#include <iostream>
#include <queue>
#include <string>
#include <vector>

template <typename T>
void ReadVector(std::vector<T>& array) {
  for (size_t i = 0; i < array.size(); ++i) {
    std::cin >> array[i];
  }
}

template <typename T>
void PrintVector(const std::vector<T>& array, char format) {
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
  std::cout << '\n';
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
T KthStatistic(std::vector<T>& array, int left, int right, int kstat) {
  int part = Partition(array, left, right);

  if (kstat < part) {
    return KthStatistic(array, left, part, kstat);
  }

  if (kstat > part) {
    return KthStatistic(array, part + 1, right, kstat);
  }

  return array[part];
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

void FillVector(std::vector<int>& array, int num) {
  int a0_elem;
  int a1_elem;
  const int kFirstKof = 123;
  const int kSecondKof = 45;
  const int kModule = 10004321;
  std::cin >> a0_elem >> a1_elem;

  array.push_back(a0_elem);
  array.push_back(a1_elem);
  for (int i = 0; i < num - 2; ++i) {
    int cur_elem;
    cur_elem =
        (1LL * kFirstKof * a1_elem + 1LL * a0_elem * kSecondKof) % kModule;
    a0_elem = a1_elem;
    a1_elem = cur_elem;
    array.push_back(cur_elem);
  }
}

int main() {
  int num;
  int order;
  std::cin >> num >> order;
  std::vector<int> array;
  FillVector(array, num);
  std::cout << KthStatistic(array, 0, num - 1, order - 1);
  return 0;
}