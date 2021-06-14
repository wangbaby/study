#!/bin/bash

# &&
# 若 cmd1 执行完毕且正确执行($?=0)，则开始执行 cmd2。 2. 若 cmd1 执行完毕且为错误 ($?≠0)，则 cmd2 不执行
# ||
# 若 cmd1 执行完毕且正确执行($?=0)，则 cmd2 不执行。 2. 若 cmd1 执行完毕且为错误 ($?≠0)，则开始执行cmd2
# ;
# cmd1 ; cmd2 连续执行多条命令

bash os/shell/test/exit.sh && echo "&& success"
bash os/shell/test/exit.sh || echo "|| success"
bash os/shell/test/exit.sh ; echo "; success"