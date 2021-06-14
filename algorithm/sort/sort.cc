/**
 * 对一组数组进行排序的思考
 * - 这组数据有什么特征
 * - 有没有可能包含大量的重复元素。如果有这种可能，三路快排可能是更好的选择
 * -
 * 是否数据的取值范围非常有限，比如对学生成绩排序。如果有这种可能，计数排序是更好的选择
 *
 * 对排序有什么额外的要求
 * - 是否需要稳定排序。如果有这种需求，归并排序可能是更好选择。
 * - 数据的存储状况是怎样的
 * - 是否是链式存储。如果是的话， 归并排序可能是更好选择
 * -
 * 数据的大小是否可以装载在内存里。如果数据量很大，内存很小，需要使用外排序算法
 */

/**
 * 稳定性
 * 稳定性的意义在于业务需要，可以保证排序前后相等数据相对位置不变。一般用于比较含有多种属性的类，
 * 例如Person Student等。 可以通过自定义比较函数，让排序算法不存在稳定性的问题。
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <utility>

using namespace std;

namespace SortTestHelper {
/**
 * 生成n个大小的数组，数组范围在range_l, range_r之间
 */
template <class T> int *GenerateRandomArray(int n, T range_l, T range_r) {
  T *arr = new T[n];
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % (range_r - range_l + 1) + range_l;
  }
  return arr;
}

/**
 * 生成近乎n个近乎有序的数组，任意交换swap_times次数组内元素
 */
template <class T> int *GenerateNearlyOrderedArray(int n, unsigned swap_times) {
  T *arr = new T[n];
  for (int i = 0; i < n; i++) {
    arr[i] = i;
  }
  srand(time(NULL));
  for (int i = 0; i < swap_times; i++) {
    unsigned x = rand() % n;
    unsigned y = rand() % n;
    swap(arr[x], arr[y]);
  }
  return arr;
}

/**
 * 判断数组是否有序
 */
template <class T> bool IsSorted(T arr[], int n) {
  for (int i = 1; i < n; i++) {
    if (arr[i - 1] > arr[i]) {
      return false;
    }
  }
  return true;
}

/**
 * 测试函数，输出排序算法名称以及花费时间
 */
template <class T>
void SortTest(const string &name, T arr[], int n, void (*sort)(T[], int)) {
  clock_t start_time = clock();
  sort(arr, n);
  clock_t end_time = clock();
  if (IsSorted(arr, n)) {
    cout << name << ": ";
    printf("%.9lf\n", (double(end_time - start_time) / CLOCKS_PER_SEC));
  } else
    cout << "Sort Failed" << endl;
}

/**
 * 输出数组元素
 */
template <class T> void ShowArray(T arr[], int n) {
  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  cout << endl;
}

/**
 * 拷贝数组
 */
template <class T> T *CopyArray(T arr[], int n) {
  T *copied_arr = new T[n];
  copy_n(arr, n, copied_arr);

  return copied_arr;
}
/**
 * O(n^2) 排序算法
 */

/**
 * 选择排序
 */
template <class T> void SelectionSort(T arr[], int n) {
  // 从[i, n)内选择最小的元素和arr[i]交换(0<=i<n)
  for (int i = 0; i < n; i++) {
    int min_index = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_index])
        min_index = j;
    }
    swap(arr[i], arr[min_index]);
  }
}

/**
 * 插入排序
 */
template <class T> void InsertionSort(T arr[], int n) {
  // 把i 插入到[0,i-1]中，使之有序
  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
      swap(arr[j], arr[j - 1]);
    }
  }
}

// 优化插入排序
template <class T> void InsertionSort2(T arr[], int n) {
  // 把swap变为赋值,因为一次swap相当于三次赋值,
  // 先保存当前元素，最后把值赋给它应该在的位置
  for (int i = 1; i < n; i++) {
    int temp = arr[i], j = i;
    for (j = i; j > 0 && temp < arr[j - 1]; j--)
      arr[j] = arr[j - 1];
    if (j != i)
      arr[j] = temp;
  }
}
/**
 * 冒泡排序
 */
template <class T> void BubbleSort(T arr[], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = n - 1; j > i; j--) {
      if (arr[j] < arr[j - 1])
        swap(arr[j], arr[j - 1]);
    }
  }
}
// 冒泡优化：不再发生交换时，排序完成；
template <class T> void BubbleSort2(T arr[], int n) {
  bool flag = false;
  for (int i = 0; i < n && !flag; i++) {
    flag = true;
    for (int j = n - 1; j > i; j--) {
      if (arr[j] < arr[j - 1]) {
        swap(arr[j], arr[j - 1]);
        flag = false;
      }
    }
  }
}

// 冒泡优化：保存最后一次发生交换的位置
template <class T> void BubbleSort3(T arr[], int n) {
  bool flag = false;
  // k: 一次冒泡过程中最后要处理的节点， pos:最后一次交换发生的位置
  int k = 0, pos = 0;
  for (int i = 0; i < n && !flag; i++) {
    flag = true;
    for (int j = n - 1; j > k; j--) {
      if (arr[j] < arr[j - 1]) {
        pos = j;
        flag = false;
        swap(arr[j], arr[j - 1]);
      }
    }
    k = pos;
  }
}

/**
 * 希尔排序
 *
 * 希尔排序是希尔（Donald
 * Shell）于1959年提出的一种排序算法。希尔排序也是一种插入排序，它是简单插入排序经过改进之后的一个更高效的版本，
 * 也称为缩小增量排序，同时该算法是冲破O(n2）的第一批算法之一。
 *
 * 希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，
 * 整个文件恰被分成一组，算法便终止。
 *
 * 简单插入排序很循规蹈矩，不管数组分布是怎么样的，依然一步一步的对元素进行比较，移动，插入，比如[5,4,3,2,1,0]这种倒序序列，
 * 数组末端的0要回到首位置很是费劲，比较和移动元素均需n-1次。而希尔排序在数组中采用跳跃式分组的策略，通过某个增量将数组元素划分为若干组，
 * 然后分组进行插入排序，随后逐步缩小增量，继续按组进行插入排序操作，直至增量为1。
 * 希尔排序通过这种策略使得整个数组在初始阶段达到从宏观上看基本有序，小的基本在前，大的基本在后。然后缩小增量，到增量为1时，
 * 其实多数情况下只需微调即可，不会涉及过多的数据移动。
 *
 * 希尔排序中对于增量序列的选择十分重要，直接影响到希尔排序的性能。增量序列{n/2,(n/2)/2...1}(希尔增量)，
 * 其最坏时间复杂度依然为O(n2)，一些经过优化的增量序列如Hibbard经过复杂证明可使得最坏时间复杂度为O(n3/2)。
 */

template <class T> void ShellSort(T arr[], int n) {
  for (int gap = n / 2; gap > 0; gap--) {
    for (int i = 0; i < gap; i++) {
      for (int j = i + gap; j < n; j += gap) {
        for (int k = j; k > 0 && arr[k] < arr[k - gap]; k -= gap) {
          swap(arr[j], arr[j - gap]);
        }
      }
    }
  }
}

/**
 * 归并排序
 */
template <class T> void InsertionSort_(T arr[], int l, int r) {
  for (int i = l + 1; i <= r; i++) {
    T temp = arr[i];
    int j;
    for (j = i; j >= l + 1 && arr[j - 1] > temp; j--)
      arr[j] = arr[j - 1];
    if (j != i)
      arr[j] = temp;
  }
}

template <class T> void Merge_(T arr[], int l, int mid, int r) {
  // 将[l, r]的元素拷贝到临时空间用于存储

  // 另外一种优化思路:不在每次Merge_里面申请释放内存，而是在MergeSort里面统一申请跟arr一样大的内存空间
  // 并且把该数组传递到接下来的处理函数中，这样也不用进行索引的判断，减小了计算量.

  T *aux = new T[r - l + 1];

  for (int i = l; i <= r; i++)
    aux[i - l] = arr[i];

  // 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
  int i = l, j = mid + 1;
  for (int k = l; k <= r; k++) {
    if (i > mid) // 如果左半部分元素已经全部处理完毕
      arr[k] = aux[j++ - l];
    else if (j > r) // 如果右半部分元素已经全部处理完毕
      arr[k] = aux[i++ - l];
    else if (aux[i - l] < aux[j - l]) // 左半部分所指元素 < 右半部分所指元素
      arr[k] = aux[i++ - l];
    else // 左半部分所指元素 >= 右半部分所指元素
      arr[k] = aux[j++ - l];
  }

  delete[] aux;
}
template <class T> void MergeSort_(T arr[], int l, int r) {
  // 对范围[l, r]的元素进行排序
  //  if (l >= r)
  //    return;

  // 当 r - l <= 15 时， 使用插入排序
  if (r - l <= 15) {
    InsertionSort_(arr, l, r);
    return;
  }

  int mid = l + (r - l) / 2;
  MergeSort_(arr, l, mid);
  MergeSort_(arr, mid + 1, r);
  // 当arr[mid] <= arr[mid + 1] 时不需要归并，此时已经有序
  if (arr[mid] > arr[mid + 1])
    Merge_(arr, l, mid, r);
}

template <class T> void MergeSort(T arr[], int n) { MergeSort_(arr, 0, n - 1); }

// 自底向上的归并排序, 无优化
template <class T> void MergeSortBU(T arr[], int n) {

  for (int sz = 1; sz <= n; sz += sz)
    for (int i = 0; i < n; i += sz + sz)
      // 对 arr[i...i+sz-1] 和 arr[i+sz...i+2*sz-1] 进行归并
      Merge_(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1));
}

/**
 * 快速排序
 *
 * parttion和归并排序 merge相比，虽然复杂度均为O(nlogn),但其常数项要小
 *
 * 随机快排在大样本的情况下，长期期望是O(NlogN)，空间复杂度是O(logN)，因此一般工程实现上都采用随机快速排序
 */

// 返回pos,使得 arr[l...pos - 1] < arr[p], arr[pos+1, r] > arr[p]
template <class T> int partition(T arr[], int l, int r) {
  // 当数组有序时，每次都取数组第一位当作标准的话，快速排序退化为n^2复杂度；因为不能将数组平分
  swap(arr[l], arr[rand() % (r - l + 1) + l]);

  T temp = arr[l];
  int pos = l;
  for (int i = l + 1; i <= r; i++) {
    if (arr[i] < temp) {
      swap(arr[i], arr[pos + 1]);
      pos++;
    }
  }

  swap(arr[pos], arr[l]);
  return pos;
}
// 双路快速排序

// 当数组中重复元素多时，按照上面的patition过程，pos左侧为小于首元素的值，右边为大于等于首元素的值，这样数组会被划分的不够均匀，导致递归深度向n
// ^ 2靠拢。
// 设计新的partition算法，使得跟首元素相等的元素，均匀的分布在pos左右两边，以便数组均匀划分

// arr[i] < temp 而不是arr[i] <= temp 的思考
// 比如数组 1,0,0, ..., 0, 0
// a. 对于arr[i]<v和arr[j]>v的方式，第一次partition得到的分点是数组中间；
// b.对于arr[i]<=v和arr[j]>=v的方式，第一次partition得到的分点是数组的倒数第二个
// 这是因为对于连续出现相等的情况，a方式会交换i和j的值；而b方式则会将连续出现的这些值归为其中一方，使得两棵子树不平衡

template <class T> int partition2(T arr[], int l, int r) {
  swap(arr[l], arr[rand() % (r - l + 1) + l]);

  T temp = arr[l];
  int i = l + 1, j = r;
  while (i <= j) {
    while (i <= r && arr[i] < temp)
      i++;
    while (j >= l + 1 && arr[j] > temp)
      j--;
    if (i > j)
      break;
    swap(arr[i++], arr[j--]);
  }

  swap(arr[l], arr[j]);
  return j;
}

// 三路快速排序

// 处理包含有大量重复元素的数组时，速度比双路/普通快速排序要快；处理普通数组时，速度也有保障
template <class T> void QuickSort2_(T arr[], int l, int r) {
  if (r - l <= 15) {
    InsertionSort_(arr, l, r);
    return;
  }
  swap(arr[l], arr[rand() % (r - l + 1) + l]);
  T temp = arr[l];

  // [l + 1, lt] < temp;
  // [ gt, r] > temp;
  // [lt + 1, i) == temp;
  int i = l + 1, lt = l, gt = r + 1; // 上面集合初始化时全部为空
  while (i < gt) {
    if (arr[i] > temp)
      swap(arr[i], arr[--gt]);
    else if (arr[i] < temp)
      swap(arr[++lt], arr[i++]);
    else
      i++;
  }

  swap(arr[l], arr[lt]);
  QuickSort2_(arr, l, lt - 1);
  QuickSort2_(arr, gt, r);
}

template <class T> void QuickSort_(T arr[], int l, int r) {
  // 实现一
  //  if (l >= r)
  //    return;

  // 实现二
  if (r - l <= 15) {
    InsertionSort_(arr, l, r);
    return;
  }

  // int pos = partition(arr, l, r);
  int pos = partition2(arr, l, r);
  QuickSort_(arr, l, pos - 1);
  QuickSort_(arr, pos + 1, r);
}

template <class T> void QuickSort(T arr[], int n) {
  srand(time(NULL));
  // QuickSort_(arr, 0, n - 1);
  // 三路快排
  QuickSort2_(arr, 0, n - 1);
}

template <class T> void shift_down(T *arr, int n, int pos) {
  while (pos * 2 + 1 < n) {
    int temp = pos * 2 + 1;
    if (temp + 1 < n)
      temp = arr[temp] < arr[temp + 1] ? temp + 1 : temp;

    if (arr[pos] < arr[temp]) {
      swap(arr[pos], arr[temp]);
      pos = temp;
    } else
      break;
  }
}

template <class T> void HeapSort(T arr[], int n) {
  for (int i = (n - 1) / 2; i >= 0; i--)
    shift_down(arr, n, i);

  for (int i = n - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    shift_down(arr, i, 0);
  }
}

} // namespace SortTestHelper

int main() {
  const int n = 100000;
  int *arr = SortTestHelper::GenerateRandomArray(n, 1, 10);
  // int *copied_arr = SortTestHelper::CopyArray(arr, n);
  //  SortTestHelper::SortTest("Insertion Sort", arr, n,
  //                           SortTestHelper::InsertionSort);
  SortTestHelper::SortTest("Heap Sort", arr, n, SortTestHelper::HeapSort);
  //  SortTestHelper::ShowArray(arr, n);
  //  SortTestHelper::ShowArray(copied_arr, n);

  delete[] arr;
  // delete[] copied_arr;

  return 0;
}