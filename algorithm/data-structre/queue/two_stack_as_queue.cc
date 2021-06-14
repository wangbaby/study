#include <stack>
using namespace std;

class MyQueue {
public:
  stack<int> s1;
  stack<int> s2;

  //入队：直接s1进栈即可
  bool EnQueue(int elem) {
    s1.push(elem);
    return true;
  }

  //出队：若s2为空，需将s1中的元素一一出栈进入s2中，再将s2出栈
  //      若s2本身不为空，直接将s2出栈
  bool DeQueue() {
    if (s1.empty() && s2.empty()) {
      return false;
    }
    if (s2.empty()) {
      while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
      }
    }
    if (!s2.empty()) {
      s2.pop();
      return true;
    }
  }
};