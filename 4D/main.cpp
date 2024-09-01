#include <iostream>
#include <vector>

struct Point {
  int x_crd;
  int y_crd;
  int z_crd;
};

template <typename T>
class BinaryIndexedTree {
 public:
  BinaryIndexedTree();

  void Update(Point point, int val);

  int GetSum(int x_crd, int y_crd, int z_crd);

  int GetRangeSum(Point point1, Point point2);

 private:
  std::vector<std::vector<std::vector<T>>> sum_;
  const int kMaxSize = 128;
};

int main() {
  int size;
  std::cin >> size;
  BinaryIndexedTree<int> tree;
  while (true) {
    int request;
    std::cin >> request;
    switch (request) {
      case 1: {
        int value;
        Point point;
        std::cin >> point.x_crd >> point.y_crd >> point.z_crd >> value;
        tree.Update(point, value);
        break;
      }
      case 2: {
        Point point1;
        Point point2;
        std::cin >> point1.x_crd >> point1.y_crd >> point1.z_crd;
        std::cin >> point2.x_crd >> point2.y_crd >> point2.z_crd;
        std::cout << tree.GetRangeSum(point1, point2) << '\n';
        break;
      }
      case 3: {
        return 0;
      }
    }
  }
  return 0;
}

template <typename T>
int BinaryIndexedTree<T>::GetRangeSum(Point point1, Point point2) {
  int sum1 = GetSum(point2.x_crd, point2.y_crd, point2.z_crd);

  int sum2 = -GetSum(point1.x_crd - 1, point2.y_crd, point2.z_crd) -
             GetSum(point2.x_crd, point1.y_crd - 1, point2.z_crd) -
             GetSum(point2.x_crd, point2.y_crd, point1.z_crd - 1);

  int sum3 = GetSum(point1.x_crd - 1, point1.y_crd - 1, point2.z_crd) +
             GetSum(point1.x_crd - 1, point2.y_crd, point1.z_crd - 1) +
             GetSum(point2.x_crd, point1.y_crd - 1, point1.z_crd - 1);

  int sum4 = -GetSum(point1.x_crd - 1, point1.y_crd - 1, point1.z_crd - 1);

  return sum1 + sum2 + sum3 + sum4;
}

template <typename T>
int BinaryIndexedTree<T>::GetSum(int x_crd, int y_crd, int z_crd) {
  int sum = 0;
  int y1_crd = 0;
  while (x_crd >= 0) {
    y1_crd = y_crd;
    while (y1_crd >= 0) {
      int z1_crd = z_crd;
      while (z1_crd >= 0) {
        sum += sum_[x_crd][y1_crd][z1_crd];
        z1_crd = (z1_crd & (z1_crd + 1)) - 1;
      }
      y1_crd = (y1_crd & (y1_crd + 1)) - 1;
    }
    x_crd = (x_crd & (x_crd + 1)) - 1;
  }
  return sum;
}

template <typename T>
BinaryIndexedTree<T>::BinaryIndexedTree() {
  sum_.resize(kMaxSize);
  for (int i = 0; i < kMaxSize; ++i) {
    sum_[i].resize(kMaxSize);
    for (int j = 0; j < kMaxSize; ++j) {
      sum_[i][j].resize(kMaxSize);
    }
  }
}

template <typename T>
void BinaryIndexedTree<T>::Update(Point point, int val) {
  int y1_crd = 0;
  while (point.x_crd < kMaxSize) {
    y1_crd = point.y_crd;
    while (y1_crd < kMaxSize) {
      int z1_crd = point.z_crd;
      while (z1_crd < kMaxSize) {
        sum_[point.x_crd][y1_crd][z1_crd] += val;
        z1_crd |= z1_crd + 1;
      }
      y1_crd |= y1_crd + 1;
    }
    point.x_crd |= point.x_crd + 1;
  }
}