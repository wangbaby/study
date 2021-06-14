# 多个进程监听同一端口

## 通过 fork 创建子进程的方式可以实现父子进程监听相同的端口

方法：在绑定端口号（bind函数）之后，监听端口号之前（listen函数），用fork（）函数生成子进程，这样子进程就可以克隆父进程，达到监听同一个端口的目的。

[fork](listen_same_port_by_fork.py)

## 通过linux内核的SO_REUSEPORT选项实现多个进程监听相同的端口

[reuseport](listen_same_port_by_reuseport.py)


# 惊群问题


