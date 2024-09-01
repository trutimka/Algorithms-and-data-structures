#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class SparseTable {
 public:
  explicit SparseTable(const std::vector<T>& array);

  T GetSecondElementOnRange(int left, int right);

 private:
  std::vector<std::vector<std::pair<int, int>>> table_;
  std::vector<T> array_;
  const int kSize = 500;
};

void SetFastStream();

template <typename T>
void ReadVector(std::vector<T>& array, std::istream& input);

int main() {
  SetFastStream();
  int size;
  int count;
  std::cin >> size >> count;
  std::vector<int> array(size);
  ReadVector(array, std::cin);

  SparseTable<int> table(array);

  for (int i = 0; i < count; ++i) {
    int left;
    int right;
    std::cin >> left >> right;

    std::cout << table.GetSecondElementOnRange(left - 1, right - 1) << '\n';
  }
  return 0;
}

void SetFastStream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

template <typename T>
void ReadVector(std::vector<T>& array, std::istream& input) {
  for (auto& item : array) {
    input >> item;
  }
}

template <typename T>
SparseTable<T>::SparseTable(const std::vector<T>& array) : array_(array) {
  int size = static_cast<int>(array.size());
  int log_size = static_cast<int>(log2(array.size())) + 1;
  table_ = std::vector<std::vector<std::pair<int, int>>>(
      array.size() * 2, std::vector<std::pair<int, int>>(
                            log_size, {std::numeric_limits<T>::max(),
                                       std::numeric_limits<T>::max()}));

  for (int i = 0; i < size; ++i) {
    table_[i][0].first = i;
  }
  for (int j = 1; (1 << j) <= size; ++j) {
    for (int i = 0; (i + (1 << j) - 1) < size; ++i) {
      auto prev1 = table_[i][j - 1];
      auto prev2 = table_[i + (1 << (j - 1))][j - 1];
      if (prev1.first == prev2.first) {
        if (array_[prev1.second] < array_[prev2.second]) {
          table_[i][j] = {prev1.first, prev1.second};
          continue;
        }
        table_[i][j] = {prev1.first, prev2.second};
        continue;
      }
      if (array_[prev1.first] < array_[prev2.first]) {
        if (prev1.second == std::numeric_limits<T>::max() ||
            array_[prev2.first] < array_[prev1.second]) {
          table_[i][j] = {prev1.first, prev2.first};
          continue;
        }
        table_[i][j] = {prev1.first, prev1.second};
        continue;
      }
      if (prev2.second == std::numeric_limits<T>::max() ||
          array_[prev1.first] < array_[prev2.second]) {
        table_[i][j] = {prev2.first, prev1.first};
      } else {
        table_[i][j] = {prev2.first, prev2.second};
      }
    }
  }
}

template <typename T>
T SparseTable<T>::GetSecondElementOnRange(int left, int right) {
  int pos = static_cast<int>(log2(right - left + 1));
  auto prev1 = table_[left][pos];
  auto prev2 = table_[right - (1 << pos) + 1][pos];
  if (prev1 != prev2) {
    if (prev1.first == prev2.first) {
      return std::min(array_[prev1.second], array_[prev2.second]);
    }
    if (array_[prev1.first] < array_[prev2.first]) {
      if (prev1.second == std::numeric_limits<T>::max()) {
        return array_[prev2.first];
      }
      return std::min(array_[prev1.second], array_[prev2.first]);
    }
    if (prev2.second == std::numeric_limits<T>::max()) {
      return array_[prev1.first];
    }
    return std::min(array_[prev2.second], array_[prev1.first]);
  }
  return array_[prev1.second];
}