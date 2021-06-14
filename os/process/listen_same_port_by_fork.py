#!/usr/bin/env python3

import socket
import os


if __name__ == '__main__':
    pid = os.getpid()
    s1 = socket.socket()
    host = '127.0.0.1'
    port1 = 12347

    s1.bind((host, port1))
    pid1 = os.fork()
    print("我会被主子进程分别执行一次")
    s1.listen(5)

    while True:
        if pid1 == 0:
            print("子进程")
            socket1, addr1 = s1.accept()
            print(addr1)
            socket1.send("子进程响应".encode('utf-8'))
            socket1.close()
            print('结束服务端子进程')
        else:
            print("主进程")
            socket2, addr2 = s1.accept()
            print(addr2)
            socket2.send("主进程响应".encode('utf-8'))
            socket2.close()
            print('结束服务端主进程')
