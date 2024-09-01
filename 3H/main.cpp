#include <iostream>
#include <string>

int FindLongestValidSubstring(const std::string& str);

int main() {
  std::string input;
  std::cin >> input;
  std::cout << FindLongestValidSubstring(input);
  return 0;
}

int FindLongestValidSubstring(const std::string& str) {
  int max_len = 0;
  int open_count = 0;
  int close_count = 0;

  for (char chr : str) {
    if (chr == '(') {
      open_count++;
    } else {
      close_count++;
    }

    if (open_count == close_count) {
      if (max_len < 2 * open_count) {
        max_len = 2 * open_count;
      }
    } else if (close_count > open_count) {
      open_count = 0;
      close_count = 0;
    }
  }

  open_count = 0;
  close_count = 0;

  for (int i = static_cast<int>(str.size()) - 1; i >= 0; --i) {
    if (str[i] == '(') {
      open_count++;
    } else {
      close_count++;
    }

    if (open_count == close_count) {
      if (max_len < 2 * open_count) {
        max_len = 2 * open_count;
      }
    } else if (open_count > close_count) {
      open_count = 0;
      close_count = 0;
    }
  }

  return max_len;
}
