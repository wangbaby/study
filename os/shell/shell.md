# shell

登陆的时候，系统会给用户一个shell 来工作.而这个登录取得的shell就记录在 /etc/passwd 

## zsh

### oh-my-zsh

```
sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
```

### ~/.zshrc

#### plugins

仓库:  https://github.com/robbyrussell/oh-my-zsh/wiki/Plugins

##### zsh-autosuggestions 

```
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
// .zshrc
plugins=(zsh-autosuggestions)
```

##### zsh-syntax-highlighting 

```
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

plugins=( [plugins...] zsh-syntax-highlighting)
```

### theme

```
ZSH_THEME="ys"
```

# 运行 Shell 脚本

## 作为可执行程序
```
chmod +x ./test.sh  # 使脚本具有执行权限
./test.sh  # 执行脚本
```
注意，一定要写成 ./test.sh，而不是 test.sh，运行其它二进制的程序也一样，直接写 test.sh，linux 系统会去 PATH 里寻找有没有叫 test.sh 的，而只有 /bin, /sbin, /usr/bin，/usr/sbin 等在 PATH 里，你的当前目录通常不在 PATH 里，所以写成 test.sh 是会找不到命令的，要用 ./test.sh 告诉系统说，就在当前目录找。

## 作为解释器参数

这种运行方式是，直接运行解释器，其参数就是 shell 脚本的文件名，如：
```
/bin/sh test.sh
/bin/php test.php
```
这种方式运行的脚本，不需要在第一行指定解释器信息，写了也没用

# 配置文件
## login shell的配置文件
 
login shell:取得 bash 时需要完整的登陆流程的，就称为 login shell。

X window 登陆 Linux 后， 再以 X 的图形化接口启动终端机，此时那个终端接口并没有需要再次的输入帐号与密码,那个 bash 的环境就称为 non-login shell。在原本 的 bash 环境下再次下达 bash 这个指令，同样的也没有输入帐号密码， 那第二个 bash (子程序) 也是 non-login shell。 

- /etc/profile:这是系统整体的设置，最好不要修改这个文件; /etc/profile 还会调用 /etc/profile.d/*.sh
- ~/.bash_profile或~/.bash_login或~/.profile:属于使用者个人设置
 
## non-login shell配置文件 

 non-login shell:取得 bash 接口的方法不需要重复登陆的举动
只会读取~/.bashrc

# keyboard shortcuts
The bash shell features a wide variety of keyboard shortcuts you can use. These will work in bash on any operating system. Some of them may not work if you’re accessing bash remotely through an SSH or telnet session, depending on how you have your keys mapped.
## emacs vs. vi keybinding
The above instructions assume you’re using the default keyboard shortcut configuration in bash. By default, bash uses emacs-style keys. If you’re more used to the vi text editor, you can switch to vi-style keyboard shortcuts.
```
set -o vi
set -o emacs
```
## Working With Processes
|   shortcut  | meaning  |
|  ----  | ----  |
| Ctrl+C  | Interrupt (kill) the current foreground process running in in the terminal. This sends the SIGINT signal to the process, which is technically just a request—most processes will honor it, but some may ignore it. |
| Ctrl+Z  | Suspend the current foreground process running in bash. This sends the SIGTSTP signal to the process. To return the process to the foreground later, use the fg process_name command. |
| Ctrl+D:  | Close the bash shell. This sends an EOF (End-of-file) marker to bash, and bash exits when it receives this marker. This is similar to running the exit command. |

## Controlling the Screen

|   shortcut  | meaning  |
|  ----  | ----  |
| Ctrl+L | Clear the screen. This is similar to running the “clear” command. |
| Ctrl+S  | Stop all output to the screen. This is particularly useful when running commands with a lot of long, verbose output, but you don’t want to stop the command itself with Ctrl+C. |
| Ctrl+Q  | Resume output to the screen after stopping it with Ctrl+S. |
| 单元格  | 单元格 |
| 单元格  | 单元格 |

## Moving the Cursor

|   shortcut  | meaning  |
|  ----  | ----  |
| Ctrl+A   | Go to the beginning of the line. |
| Ctrl+E  | Go to the end of the line. |
| Alt+B  | Go left (back) one word. （ESC + B in mac)|
| Ctrl+B | Go left (back) one character. |
| Alt+F | Go right (forward) one word. (ESC + F in mac) |
| Ctrl+F  | Go right (forward) one character. |

## Deleting Cutting and Pasting
|   shortcut  | meaning  |
|  ----  | ----  |
| Ctrl+D | Delete the character under the cursor.|
| Alt+D  | Delete all characters after the cursor on the current line. （ESC + D in mac)|
| Ctrl+H | Delete the character before the cursor.|
| Ctrl+W | Cut the word before the cursor, adding it to the clipboard. |
| Ctrl+K | Cut the part of the line after the cursor, adding it to the clipboard. |
| Ctrl+U | Cut the part of the line before the cursor, adding it to the clipboard. |
| Ctrl+Y | Paste the last thing you cut from the clipboard. The y here stands for “yank”. |

## Working With Your Command History

|   shortcut  | meaning  |
|  ----  | ----  |
| Ctrl+P   | Go to the previous command in the command history. |
| Ctrl+N  | Go to the next command in the command history. |
| 单元格  | 单元格 |
| 单元格  | 单元格 |
