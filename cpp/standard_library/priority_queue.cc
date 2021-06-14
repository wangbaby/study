#include <ctime>
#include <iostream>
#include <queue>

using namespace std;

int main() {
  srand(time(NULL));
  priority_queue<int> pq;

  for (int i = 0; i < 10; i++) {
    pq.push(rand() % 100);
  }

  while (!pq.empty()) {
    int val = pq.top();
    pq.pop();
    cout << val << " -> ";
  }

  cout << endl;

  // 最小堆
  priority_queue<int, vector<int>, greater<int>> pq2;
  for (int i = 0; i < 10; i++) {
    pq2.push(rand() % 100);
  }

  while (!pq2.empty()) {
    int val = pq2.top();
    pq2.pop();
    cout << val << " -> ";
  }

  cout << endl;
  return 0;
}