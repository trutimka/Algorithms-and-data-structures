#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T>
std::vector<T> ReadArray(const size_t& size) {
  std::vector<T> array(size);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  return array;
}

template <typename T>
void PrintArray(const std::vector<T>& array) {
  for (const auto& item : array) {
    std::cout << item << ' ';
  }
  std::cout << '\n';
}

template <typename T>
T FindMin(const std::vector<T>& array, size_t left, size_t right) {
  T min = array[left];
  for (size_t i = left + 1; i < right; ++i) {
    if (min > array[i]) {
      min = array[i];
    }
  }
  return min;
}

template <typename T>
std::vector<T> BuildMinsArray(const std::vector<T>& array) {
  std::vector<T> minsarray(array.size());
  minsarray[0] = array[0];
  for (size_t i = 1; i < array.size(); ++i) {
    minsarray[i] = array[i] > minsarray[i - 1] ? minsarray[i - 1] : array[i];
  }
  return minsarray;
}

template <typename T>
double FindAnswer(size_t left, size_t right, const std::vector<T>& array) {
  size_t lenth = right - left + 1;
  double pw = array.size() * 1. / lenth;
  if (left == 0) {
    return pow(array[right], pw);
  }
  return pow(array[right] / array[left - 1], pw);
}

template <typename T>
std::vector<T> BuildParr(const std::vector<T>& arr) {
  size_t pw = arr.size();
  std::vector<T> ret(pw);
  ret[0] = pow(arr[0], 1. / pw);
  for (size_t i = 1; i < arr.size(); ++i) {
    ret[i] = ret[i - 1] * pow(arr[i], 1. / pw);
  }
  return ret;
}

int main() {
  size_t num;
  size_t req;
  const int kPrecision = 10;
  std::cin >> num;
  std::vector<double> arr = ReadArray<double>(num);
  std::vector<double> parr = BuildParr<double>(arr);
  std::cin >> req;
  for (size_t _ = 0; _ < req; ++_) {
    size_t left;
    size_t right;
    std::cin >> left >> right;
    std::cout << std::fixed << std::setprecision(kPrecision)
              << FindAnswer<double>(left, right, parr) << '\n';
  }
  return 0;
}