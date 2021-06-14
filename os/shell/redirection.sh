#!/bin/bash

echo hello >tmp/test.txt
echo world >>tmp/test.txt

cat <tmp/test.txt

nohup top >/dev/null 2>&1
