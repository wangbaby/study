/**
 * 容器存取界面:
 * 
 * 为了兼容最原始的容器-数组，迭代器的使用方法都仿照数组元素指针
 * 
 * 首先，无论容器中数组以何种方式组织，总能够以一定规则将其中的所有元素排列成一个虚拟序列
 * 其次，各种容器都可以提供相应的代理类封装所有对该类容器的虚拟数据序列的操作
 * 
 * 容器分类：
 * 序列型容器可以提供允许修改数据的迭代器，而关系型容器只能提供只读迭代器以保证容器内数据结构的正确性
 * 前向迭代器 双向迭代器 随机迭代器
 * 
 * 
 * 容器陷阱:
 * 容器中通常有以迭代器为参数对指定位置进行操作的成员函数，调用此类函数有个隐性要求，即迭代器所指数据来自该容器
 * 由于迭代器独立于容器之外，也就意味着用户可以一次生成多个迭代器对容器进行操作
 * 
 * 
 */ 