/**
 * 顺序容器： 实现能按照顺序访问的容器
 * 数据的存储位置与内容无关
 * 
 * 构造函数:
 * S(n, t) 构造含有n个t值副本的容器
 * S(i,j) 构造包含迭代器范围[i, j)内所有数据副本的容器，i/j可以为任意容器迭代器，只要满足前向迭代器即可
 * 
 * 成员函数:
 * push_back()
 * pop_back()
 * 
 * front()
 * back()
 * 
 * insert(p,t)n 在迭代器p所指之前插入数据t的副本
 * insert(p, n, t)
 * insert(p , i, j) 要求迭代器i/j不能是容器本身的迭代器
 * 
 * erase(p) 返回所删数据的后继数据的迭代器
 * erase(p, q) 返回所删数据的后继数据的迭代器
 * 
 * clear()
 * 
 * assign(p, q)
 * assign(n, t) 用t值的n个副本替代容器内原有数据 
 * 
 * resize(sz, v=T()) 修改容器尺寸为sz
 */
