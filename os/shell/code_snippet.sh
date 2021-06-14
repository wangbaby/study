#!/bin/bash

# 得到shell脚本文件所在完整路径
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)" 
echo $DIR

echo $(pwd)
