/**
* 对所容器元素基本要求：可拷贝构造
* 将容器放入容器的过程就是通过数据的拷贝构造函数在容器内创建数据的一个副本的过程, 此外各个容器的不同操作还会对容器元素有不同要求
* 
* c++标准对所有容器规定的基本要求：
* 首先容器中必须有若干与所存数据类型有关的嵌套定义类型
* C::value_type
* C::reference_type
* C::const_reference_type
* C::size_type
* 其次 容器必须拥有默认构造函数和拷贝构造函数
* C a;
* C b(a);
* 还必须提供与迭代器有关的嵌套定义类型和成员函数
* C::iterator
* C::const_iterator
* C::difference_type
* C::reverse_iterator
* C::const_reverse_iterator
* begin()
* end()
* cbegin()
* cend()
* rbegin()
* rend()
* crbegin()
* crend()
* 容器必有成员函数
* size()
* max_size()
* empty()
* swap(C &a)
* 两个同类型容器可以比较相等
* ==
* !=
*
*/