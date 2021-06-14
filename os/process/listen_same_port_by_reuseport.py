#!/usr/bin/env python3

import socket
import os

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
s.bind(('0.0.0.0', 1234))
s.listen(5)

while True:
    conn, addr = s.accept()
    print('Connected to {}'.format(os.getpid()))
    conn.close()
