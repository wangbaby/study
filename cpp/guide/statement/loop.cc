#include <iostream>
#include <vector>

using namespace std;

void f1() {}

void f2() {}

#define EMPTYMACRO \
  do {             \
  } while (0);

// #define func()                                                                 \
//   f1();                                                                        \
//   f2();

#define func() \
  {            \
    f1();      \
    f2();      \
  }

int fc() {
  int k1 = 10;
  cout << k1 << endl;
  {
    int k1 = 100;
    cout << k1 << endl;
  }
  cout << k1 << endl;
}

int main() {
  do {
  } while (0);

  int a = 1;
  if (a < 0) func();

  fc();

  // range-for
  vector<int> vi{1, 2, 3, 4, 5};
  for (auto i : vi) {
    cout << i << " ";
  }

  cout << endl;

  return 0;
}

在C++ 03 /
        98中，不同的容器和数组，遍历的方法不尽相同，写法不统一，也不够简洁 而C++ 11基于范围的for循环以统一、简洁的方式来遍历容器和数组，用起来更方便了。 与普通的for循环相比，基于范围的循环方式是“自明”的。 这种语法构成的循环不需要额外的注释或语言基础，很容易就可以看清楚它想表达的意义。 在实际项目中经常会遇到需要针对容器做遍历的情况，使用这种循环方式无疑会让编码和维护变得更加简便。

        基于范围的for循环，对于冒号前面的局部变量声明（for -
    range -
    declaration）只要求能够支持容器类型的隐式转换。 因此，在使用时需要注意，像下面这样写也是可以通过编译的：
        std::vector<int>
            arr;
for (char n : arr)
  ;  // int会被隐式转换为char
在上面的例子中，我们都是在使用只读方式遍历容器。如果需要在遍历时修改容器中的值，则需要使用引用，代码如下： for (
    auto &n : arr) {
  std::cout << n++ << std::endl;
}
在完成上面的遍历后，arr中的每个元素都会被自加1。 当然，若只是希望遍历，而不希望修改，可以使用const auto
        &来定义n的类型。 这样对于复制负担比较大的容器元素（比如一个std::<
            std::string>
            ）也可以无损耗地进行遍历。

    == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == == == 使用细节 == == == == == == == == == == == == == == == ==
    == == == == == == == == == == == == == == ==
    在使用基于范围的for循环时，还需要注意容器本身的一些约束。 std::set<int> ss =
    {1, 2, 3};
for (auto &val : ss) {
  // error: increment of read-only reference 'val'
  std::cout << val++ << std::endl;
}
例子中使用auto &定义了std：：set<int>
    中元素的引用，希望能够在循环中对set的值进行修改，但std：：set的内部元素是只读的
        这是由std::的特征决定的，因此，for循环中的auto &会被推导为const int
            &。 同样的细节也会出现在std::
                的遍历中。基于范围的for循环中的std引用，是不能够修改first的。

    基于范围的for循环其实是普通for循环的语法糖，因此，同普通的for循环一样，在迭代时修改容器很可能会引起迭代器失效，导致一些意料之外的结果
        对于基于范围的for循环而言，等价的普通for循环如下： std::vector<int>
            arr = {1, 2, 3, 4, 5};
auto &&__range = (arr);
for (auto __begin = __range.begin(), __end = __range.end(); __begin != __end;
     ++__begin) {
  auto val = *__begin;
  std::cout << val << std::endl;
  arr.push_back(0);  // 扩大容器
}
从这里可以很清晰地看到，和我们平时写的容器遍历不同，基于范围的for循环倾向于在循环开始之前确定好迭代的范围，而不是在每次迭代之前
        都去调用一次arr.end（）
            当然，良好的编程习惯是尽量不要在迭代过程中修改迭代的容器。 但是实际情况要求我们不得不这样做的时候，通过理解基于范围的for循环的这个特点，就可以方便地分析每次迭代的结果，提前避免算法的错误

    == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == == == 让基于范围的for循环支持自定义类型 == == == == == == == ==
    == == == == == == == == == == == == == == == == == == == == == == ==

    基于范围的for循环只是普通for循环的语法糖。它需要查找到容器提供的begin和end迭代器 1）若容器是一个普通array对象（如int arr
        [10] ），那么begin将为array的首地址，end将为首地址加容器长度 2）若容器是一个类对象，那么range-based for将试图通过查找类的begin（）和end（）方法来定位begin、end迭代器 3）否则，range-based for将试图使用全局的begin和end函数来定位begin、end迭代器
            见range.cpp

                **********************std::function 和 bind
                    绑定器 ******************************
                        不仅让我们使用标准库函数时变得更加方便，而且还能方便地实现延迟求值