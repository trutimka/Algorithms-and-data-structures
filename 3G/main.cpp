#include <iostream>
#include <vector>

void SetStreamOutput();

template <typename T>
void ReadVector(std::vector<T>& array);

template <typename T>
int64_t FindAnswer(std::vector<T>& array);

int main() {
  SetStreamOutput();
  int count = 0;
  std::cin >> count;
  std::vector<size_t> array(count);
  ReadVector(array);
  int64_t result = FindAnswer(array);
  std::cout << result;
  return 0;
}

void SetStreamOutput() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

template <typename T>
void ReadVector(std::vector<T>& array) {
  for (size_t i = 0; i < array.size(); ++i) {
    std::cin >> array[i];
  }
}

template <typename T>
int64_t FindAnswer(std::vector<T>& array) {
  int64_t result = 0;
  size_t left_pos = 0;
  size_t right_pos = array.size() - 1;
  size_t cur_left_value = 0;
  size_t cur_right_value = 0;
  while (left_pos < right_pos) {
    if (array[left_pos] <= array[right_pos]) {
      if (cur_left_value <= array[left_pos]) {
        cur_left_value = array[left_pos];
      } else {
        result += cur_left_value - array[left_pos];
      }
      ++left_pos;
    } else {
      if (cur_right_value <= array[right_pos]) {
        cur_right_value = array[right_pos];
      } else {
        result += cur_right_value - array[right_pos];
      }
      --right_pos;
    }
  }
  return result;
}