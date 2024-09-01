#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>

template <typename T>
class HashTable {
 public:
  explicit HashTable(size_t size);

  void Insert(const T& key);
  void Insert(T&& key);

  void Erase(const T& key);

  bool Contains(const T& key) const;
  void Erase(T&& key);

  bool Contains(T&& key) const;

 private:
  size_t table_size_;
  std::vector<std::list<T>> table_;
  size_t HashFunction(const T& key) const;
};
void SetFastStream();

int main() {
  SetFastStream();
  int queries;
  std::cin >> queries;

  HashTable<int> container(queries);

  for (int i = 0; i < queries; ++i) {
    char character;
    int num;
    std::cin >> character >> num;

    switch (character) {
      case '+':
        container.Insert(std::move(num));
        break;
      case '-':
        container.Erase(std::move(num));
        break;
      case '?':
        std::cout << (container.Contains(std::move(num)) ? "YES\n" : "NO\n");
        break;
    }
  }
  return 0;
}

void SetFastStream() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

template <typename T>
bool HashTable<T>::Contains(const T& key) const {
  auto hash = HashFunction(key);
  for (auto& iter : table_[hash]) {
    if (iter == key) {
      return true;
    }
  }
  return false;
}

template <typename T>
bool HashTable<T>::Contains(T&& key) const {
  auto hash = HashFunction(std::move(key));
  return std::ranges::any_of(
      table_[hash], [key](const T& value) -> bool { return key == value; });
}

template <typename T>
size_t HashTable<T>::HashFunction(const T& key) const {
  size_t hash = std::hash<T>{}(key);
  return hash % table_size_;
}

template <typename T>
HashTable<T>::HashTable(size_t size)
    : table_size_(size), table_(std::vector<std::list<T>>(size)) {}

template <typename T>
void HashTable<T>::Insert(const T& key) {
  auto hash = HashFunction(key);
  for (auto& iter : table_[hash]) {
    if (iter == key) {
      return;
    }
  }
  table_[hash].push_back(key);
}

template <typename T>
void HashTable<T>::Insert(T&& key) {
  auto hash = HashFunction(key);
  for (auto&& iter : table_[hash]) {
    if (iter == std::move(key)) {
      return;
    }
  }
  table_[hash].push_back(std::move(key));
}

template <typename T>
void HashTable<T>::Erase(const T& key) {
  auto hash = HashFunction(key);
  auto iter = table_[hash].begin();
  while (iter != table_[hash].end()) {
    if (*iter == key) {
      table_[hash].erase(iter);
      return;
    }
    ++iter;
  }
}

template <typename T>
void HashTable<T>::Erase(T&& key) {
  auto hash = HashFunction(std::move(key));
  auto iter = table_[hash].begin();
  while (iter != table_[hash].end()) {
    if (*iter == std::move(key)) {
      table_[hash].erase(iter);
      return;
    }
    ++iter;
  }
}