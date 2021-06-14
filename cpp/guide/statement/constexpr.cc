/**
 * C++14解除了对constexpr函数的大部分限制。在C++14的constexpr函数体内我们既可以声明变量，也可以使用goto和try之外大部分的控制流语句。
 * 
 * 虽说constexpr函数所定义的是编译期的函数，但实际上在运行期constexpr函数也能被调用。事实上，如果使用编译期常量参数调用constexpr函数，我们就能够在编译期得到运算结果；而如果使用运行期变量参数调用constexpr函数，那么在运行期我们同样也能得到运算结果。
 * 
 * 准确的说，constexpr函数是一种在编译期和运行期都能被调用并执行的函数。出于constexpr函数的这个特点，在C++11之后进行数值计算时，无论在编译期还是运行期我们都可以统一用一套代码来实现。编译期和运行期在数值计算这点上得到了部分统一.
 */

#include <iostream>

constexpr int factorial(int n){
    int res = 1;
    for(int i = 1; i <= n; i++ ){
        res *= i;
    }
    return res;
}


int main(){
    std::cout << factorial(10) << std::endl;
    int n = 10;
    std::cout << factorial(n) << std::endl;

    return 0;
}
 
