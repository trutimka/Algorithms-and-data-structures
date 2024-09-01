#include <iostream>
#include <queue>
#include <string>
#include <vector>

template <typename T>
class BinaryHeap {
 public:
  explicit BinaryHeap() = default;

  void Insert(const T& value) {
    data_.push_back({value, indexes_.size()});
    indexes_.push_back(data_.size() - 1);
    ShiftUp(data_.size() - 1);
  }

  void ExtractMin() {
    std::swap(data_[0], data_[data_.size() - 1]);
    indexes_[data_[data_.size() - 1].second] = -1;
    indexes_[data_[0].second] = 0;
    data_.pop_back();
    ShiftDown(0);
  }

  T GetMin() { return data_[0].first; }

  void DecreaseKey(int index, T value) {
    if (index != -1 && indexes_[index] != -1) {
      data_[indexes_[index]].first -= value;
      ShiftUp(indexes_[index]);
    }
  }

 private:
  void ShiftDown(size_t ind) {
    if (2 * ind + 1 >= data_.size()) {
      return;
    }

    size_t next_i = 2 * ind + 1;
    if (2 * ind + 2 < data_.size() &&
        data_[2 * ind + 1].first > data_[2 * ind + 2].first) {
      next_i = 2 * ind + 2;
    }

    if (data_[ind].first > data_[next_i].first) {
      std::swap(indexes_[data_[ind].second], indexes_[data_[next_i].second]);
      std::swap(data_[ind], data_[next_i]);
      ShiftDown(next_i);
    }
  }

  void ShiftUp(size_t ind) {
    if (ind == 0) {
      return;
    }
    size_t parent = (ind - 1) / 2;
    if (data_[ind].first < data_[parent].first) {
      std::swap(indexes_[data_[ind].second], indexes_[data_[parent].second]);
      std::swap(data_[ind], data_[parent]);
      ShiftUp(parent);
    }
  }

  std::vector<std::pair<T, int>> data_;
  std::vector<int> indexes_;
};

template <typename T>
int BinSearch(const std::vector<T>& array, const T& value) {
  int left = 0;
  int right = array.size() - 1;

  while (right > left) {
    int middle = left + (right - left) / 2;
    if (array[middle] < value) {
      left = middle + 1;
    } else if (array[middle] > value) {
      right = middle - 1;
    } else {
      return middle;
    }
  }

  if (array[left] != value) {
    return -1;
  }
  return left;
}

void CheckRequest(std::string& request, std::vector<int>& indexes,
                  BinaryHeap<long long>& heap, int ind) {
  if (request == "insert") {
    long long num;
    indexes.push_back(ind + 1);
    std::cin >> num;
    heap.Insert(num);
    return;
  }

  if (request == "getMin") {
    std::cout << heap.GetMin() << '\n';
    return;
  }

  if (request == "extractMin") {
    heap.ExtractMin();
    return;
  }

  if (request == "decreaseKey") {
    int key;
    long long value;
    std::cin >> key >> value;
    int index = 0;
    index = BinSearch(indexes, key);
    heap.DecreaseKey(index, value);
  }
}

void SetStreamSettings() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
}

int main() {
  SetStreamSettings();
  int req;
  BinaryHeap<long long> heap;
  std::vector<int> indexes;
  std::cin >> req;
  for (int ind = 0; ind < req; ++ind) {
    std::string request;
    std::cin >> request;
    CheckRequest(request, indexes, heap, ind);
  }
  return 0;
}