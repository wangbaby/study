#include <cstring>
#include <iostream>

// int max_element(const int *l, size_t sz) {
//   int max_value = l[0];
//   for (size_t i = 0; i < sz; i++)
//     if (l[i] > max_value) max_value = l[i];

//   return max_value;
// }

char max_element(const char *l, size_t sz) {
  char max_value = l[0];
  for (size_t i = 0; i < sz; i++)
    if (l[i] > max_value) max_value = l[i];

  return max_value;
}
// 考虑到列表类型可能为复杂自定义类型，赋值会导致额外开销，因此将max_value该用为指针
template <typename T>
const T &max_element(const T *l, size_t sz) {
  const T *max_value(l);
  for (size_t i = 0; i < sz; i++)
    if (l[i] > *max_value) max_value = &l[i];

  return *max_value;
}

// 模板参数默认值
// 明确生成模板实例
// 重复模板实例 ->在链接时识别以及合并等价的模板实例；链接器不考虑函数具体内容，仅仅通过函数名 模板实参列表以及
// 参数列表等接口信息来判断两个函数是否等价


int main() {
  int arr[]{1, 4, 2, 3};
  std::cout << max_element<int>(arr, sizeof(arr) / sizeof(int)) << std::endl;
  // 模板参数自动推导
  std::cout << max_element(arr, sizeof(arr) / sizeof(int)) << std::endl;

  const char *str = "hello world";
  std::cout << max_element(str, strlen(str)) << std::endl;

  return 0;
}