#include <iostream>
#include <string>
#include <unordered_map>

bool FindAnswer(std::string& small, std::string& big);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string small_string;
  std::string full_string;
  std::cin >> small_string >> full_string;
  std::string answer = FindAnswer(small_string, full_string) ? "Yes" : "No";
  std::cout << answer;
  return 0;
}

bool FindAnswer(std::string& small, std::string& big) {
  std::unordered_map<char, std::pair<int, int>> main_map;
  // first - count, second - first position
  for (auto symbol : small) {
    ++main_map[symbol].first;
    main_map[symbol].second = -1;
  }

  size_t start = 0;
  size_t cur_size = 0;

  auto copy = main_map;
  for (size_t i = 0; i < big.size(); ++i) {
    if (copy.find(big[i]) == copy.end()) {
      start = i + 1;
      copy = main_map;
      cur_size = 0;
      continue;
    }

    --copy[big[i]].first;
    ++cur_size;

    if (copy[big[i]].second == -1) {
      copy[big[i]].second = static_cast<int>(i);
    }

    if (copy[big[i]].first < 0) {
      auto finish = static_cast<size_t>(copy[big[i]].second);
      while (start <= finish) {
        ++copy[big[start]].first;
        ++start;
        --cur_size;
      }
    }

    if (cur_size == small.size()) {
      return true;
    }
  }
  return false;
}