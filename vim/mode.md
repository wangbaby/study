可视模式

Vim 具有 3 种不同的可视模式，分别用于操作字符文本、行文本或块文本。

某些可视模式命令执行的基本功能与普通模式相同，但操作上有些细微的变化。 例如，在这两种模式中， c 命令的功能是一样的，都是删除指定的文本并切换到插入模式。不过，要指定其所操作的范围，二者的方式却不甚相同。在普通模式中，我们 先触发修改命令，然后使用动作命令指定其作用范围。然而在可视模式中，我们先选中选区，然后 再触发修改命令。这种次序颠倒的方式对所有的操作符命令都适用。

v / V / <C-v>切换到面向（字符/行/列)的可视模式。再次按键切换到普通模式。o切换高亮选取的活动端

可视模式下I 命令和 A 命令分别把光标置于选区的开头和结尾。

插入模式

操作命令
A行尾添加a当前光标后添加i当前光标前添加I行首添加o向下新增一行并进入插入模式O向上新增一行并进入插入模式r替换单个字符<C-h>删除前一个字符<C-w>删除前一个单词<C-u>删除至行首<C-o>先切换到普通模式然后返回到插入模式<C-r>{register}插入寄存器内容:<C-R> + 复制系统剪贴板<C-n>单词补全Ctrl + p：功能同上，只是默认选中的是列表最后一个单词

命令行模式

命令行模式会提示我们输入一条 Ex 命令、一个查找模式，或一个表达式，即在按 / 调出查找提示符或用 <C-r>= 访问表达式寄存器时，命令行模式也会被激活。

操作范围

1文件第一行.文件当前行$文件最后一行%文件所有行'<, '>如果我们先执行 2G， 再跟着执行 VG，符号 '< 是代表高亮选区首行的位置标记，而 '> 则代表高亮选区的最后一行，这些位置标记即使在退出可视模式后仍然 存在。:/{pattern}/,/{pattern}/p模式作为地址'm包含位置m的标记

eg:

:d当前行:.d当前行:1d第一行:$d最后一行:1,$d所有行:%d所有行:.,5d当前行至第 5 行:,5d当前行至第 5 行:,+3d当前行及接下来的 3 行:1,+3d第一行至当前行再加 3 行:,-3d当前行及向上的 3 行:3,'xd第三行至标注 为 x 的那一行:/^foo/,$d当前行以下，以字符 “foo” 开头的那一行至结尾:/^foo/+1,$d当前行以下，以字符 “foo” 开头的那一行的下一行至结尾

除了,外，; 也可以分割行号用于表示Vim操作范围。区别在于，a,b 的 b 是以当前行作为参考，而 a;b 的 b 是以 a 行作为参考.
例如，假设当前光标所在为第 5 行，:1,+1d 命令会删除第 1 行至第 6 (5+1) 行，而 :1;+1d 命令则会删除第 1 行和第 2(1+1) 行。

如果想设置多个寻找条件，只需要在条件前再加上 /，比如：
:/foo//bar//quux/d

上面的命令首先在当前行之后寻找第一个包含 “foo” 字符的那一行，然后在找到的这一行之后寻找第一个包含 “bar” 字符的那一行，然后再在找到的这一行之后寻找第一个包含 “quux” 的那一行, 最后删除的对象就是最后找到的这一行

文本操作命令

命令用途[range]delete [x]删除指定范围内的行到寄存器x中[range]yank [x]复制指定范围内的行到寄存器x中[line]put [x]在指定行后粘贴寄存器x中的内容[range]copy {address} (copy=>co=>t)把指定范围内的行拷贝到address所指定的行之下（不使用寄存器）[range]move {address} (move=>m)把指定范围内的行移动到address所指定的行之下[range]normal {commands}对指定范围内的每一行执行普通模式命令commands[range]subsitute/{pattern}/{string}/[flags]把指定范围内出现{pattern}的地方替换为{string}[range]g[lobal][!]/{pattern}/[cmd]用于指示Vim在 [range] 界定范围内对 (不) 匹配模式 {pattern} 的文本行执行 Ex 命令 [cmd]。Vim :global 命令的默认作用范围是整个文件 (用%表示)pattern指定 global 命令要匹配的目标模式，若将该域留空，Vim会自动使用当前(最近一次)的查找模式cmd为 除 :global 命令之外的任何 Ex 命令，Vim缺省使用 :print 命令 (缩写 :p)如果想删除vim当前打开文件中的所有空白行，可使用vim命令 :g/^\s*$/d 实现[range]print （print => p）打印内容x:wq   强制性写入文件并退出。即使文件没有被修改也强制写入，并更新文件的修改时间。:x    写入文件并退出。仅当文件被修改时才写入，并更新文件修改时间，否则不会更新文件修改时间。这两者一般情况下没什么不一样，但是在编程方面，对编辑源文件可能会产生重要影响。因为文件即使没有修改，":wq"强制更新文件的修改时间，这样会让make编译整个项目时以为文件被修改过了，然后就得重新编译链接生成可执行文件。这可能会产生让人误解的后果，当然也产生了不必要的系统资源花销。e重新加载文件e! 强制从磁盘加载文件w:write a.txt 可将 Vim 当前打开的文件另存为新文件 a.txt。此外，:saveas b.txt (缩写形式 :sav a.txt) 也可将当前打开的文件另存为新文件 a.txt

分屏

vsp:vsplit filename 或缩写形式 :vsp filename 可实现Vim垂直方向分割屏幕，且打开新的文件 filenamesp:split filename 或缩写形式 :sp filename 可实现在Vim水平方向分割屏幕，且打开新的文件 filename

命令行窗口

q/  (普通模式下)打开查找命令历史的命令行窗口 q: (普通模式下)打开 Ex 命令历史的命令行窗口<Ctrl-f>  (命令行模式下)从命令行模式切换到命令行窗口

标签页

tabedit [filename]打开一个新的标签页。如果省略了filename参数的话，vim会创建一个新标签页，里面包含一个空缓冲区。tabc[lose]关闭当前标签页及其中的所有窗口tabo[nly]只保留活动标签页，关闭所有其他标签页gt / gT  (gt => :tabn[ext], gT=>:tabp[reviouse)跳转到上一个/下一个 标签页

缓冲区

ls / buffers列出所有被载入到内存中的缓冲区的列表，%符号指明哪个缓冲区在当前窗口中可见:ls命令获得的Vim缓冲区列表开头的数字是在缓冲区创建时由Vim自动分配的编号(且无法手动更改)，使用:buffer n命令直接凭编号n跳转到该缓冲区bnext / bprev正向或反向遍历列表，命令Ctrl + ^可以在当前文件和轮换文件间快速切换bfirst / blast跳转到Vim缓冲区列表的开头和结尾bdelete命令格式为:bdelete n1 n2 n3 或 :n,m bdelete，前者用于删除特定缓冲区，后者用于删除一个编号区间段的缓冲区.删除一个缓冲区并不会影响缓冲区所关联的磁盘文件，只是把该文件在内存中的映像删掉

其他

version显示版本信息及默认vimrc配置文件加载路径setset all 查看所有环境变量的设置set 查看所有与系统默认不同的环境变量以ignorecase为例，这是一个布尔选项1. set ignorecase 打开2. set noignorecase 关闭3. set ignorecase! 反转4. set ignorecase? 查询状态5. set ignorecase& 恢复默认值setlocalvim的设置项通常全局生效， 但是有些选项只对一个窗口或者缓冲区生效。!{shell cmd}调用shell命令 eg: :!node %shell启动交互式shellExplore命令或缩写:E命令将在当前窗口中打开文件浏览器Sexplore或缩写:Sex将在水平拆分窗口中打开文件浏览器：

搜索模式

在Vim命令模式下，输入 / 或 ? 符号就进入了搜索模式，/ 用于正向往下搜索，? 用于反向往上搜索。

注意：搜索一些特殊的字符，例如：*、[、]、^、%、/、?、~、$等，需要在它们的前面加上转义符号\。

默认Vim搜索命令是大小写敏感的，因此，搜索 the 不会查找到 The。使用命令 :set ignorecase 会使得Vim搜索变得不区分大小写。

不管 ignorecase 选项的值是什么，都可以在搜索命令中使用 \c 来强制使得当前搜索模式不区分大小写，而命令 \C 则会强制当前搜索模式大小写敏感。因此，/the\c 既会查找 the，也会查找到 The。

如果打开了 ignorecase 选项，那么你也应该设置 :set smartcase。当 ignorecase 和 smartcase 选项均打开时，只要你的搜索模式中包含大写字母，那Vim会认为你当前的搜索是区分大小写的，如果搜索模式中不包含任何大写字母，Vim则会认为搜索应该不区分大小写。这是个比较”智能的”推测你搜索意图的机制。

例如，在打开上述两个选项的条件下，/The 只会查找到 The，而 /the 既会查找 the，也会查找到 The等。
注意：smartcase 选项只对你手工输入的搜索模式有效，对于 *、# 或 gd 等是不起作用的。

如果想搜索当前光标所在位置的单词，可以先输入 / 进入搜索模式，然后依次输入命令 <Ctrl-r><Ctrl-w> 来复制光标下的单词并将其插入命令行中。如果想插入光标下的字串，可以使用命令 <Ctrl-r><Ctrl-a>。

进行过Vim搜索后，当 /、?、:s、:g 命令使用空的搜索模式时会沿用最近一次的搜索模式。所以，在搜索完某个单词后，使用Vim替换命令 :%s//new/g 会将之前搜索的单词全部替换为 new。

为了更好的进行搜索，Vim支持正则表达式，最基本的正则表达式规则包括：
^         表示一行的开头
$         表示一行的结尾
.         表示任意一个字符
*         匹配0次或n次

替换

Vim可以在命令行模式下使用:substitute命令将指定的字符替换成其他目标字符，通常使用该命令的缩写格式:s进行操作

Vim替换命令的基本语法是 :[range]s/源字符串/目标字符串/[option]，其中range和option字段都可以缺省不填。
各个字段的意思是：

range      表示搜索范围，默认表示当前行
s               substitute的简写，表示替换
option    表示操作类型，默认只对第一个匹配的字符进行替换
                   option字段值g(global)表示全局替换，c(comfirm)表示操作时需要确认，i(ignorecase)表示不区分大小写
                   这些选项可以组合使用


普通模式

语法说明["x]c{motion}delete {motion} text [into register x] and start insert.["x]cc / ["x]Sdelete [count] lines [into register x] and start insert.["x]Cdelete from the cursor position to the end of the line and [count] -  1 more lines [into register x], and start insert.["x]sdelete [count] characters [into register x] and start insert.["x]xdelete [count] characters under and after the cursor [into register x].["x]Xdelete [count] charactersbefore the cursor [into register x].["x]d{motion}delete text that {motion} moves over [into register x]["x]dddelete [count] lines [into register x]["x]Ddelete from the cursor position to the end of the line and [count] -  1 more lines [into register x].["x]y{motion}yank {motion} text [into register x].["x]yy / ["x]Yyank [count] lines [into register x].["x]p / ["x]Pput the text [from register x] after / before cursor [count] times.怎样才能知道 p 命令是把寄存器的文本粘贴到当前字符之后还是当前行之后 呢?这取决于这个指定的寄存器是怎样被赋值的。面向行的复制或者删除操作(例 如:dd、yy 或者 dap)，将创建面向行的寄存器;而面向字符的复制或者删除操作(例 如:x、diw 或者 das)，则创建面向字符的寄存器。["x]gp/["x]gPjust like "p/P", but leave the cursor just after the new text.g~ {motion}switch case of {motion} text.g~~ / g~g~switch case of current line.gu / gU {motion} make {motion} text lowercase / uppercase.guu gugu / gU gUUmakr current line lowercase / uppercase.

文本对象

Vim 的文本对象分为两类:一类是操作分隔符的文本对象，另 一类用于操作文本块。
文本对象自身并不是动作命令，不能用它们在文档中移动。但是却可以在可视模式及操作符待决模式中使用文本对象, 常见的例子包括 d{motion}、c{motion} 和 y{motion}。

1.操作分隔符的文本对象

以 i 开头的文本对象会选择分隔符内部的文本，而以 a 开头的文本对象则会选择包括分隔符在内的整个文本。为了便于记忆，可以把 i 想成“inside”，而把 a 想成“around” 或“all”。
a)  i)圆括号a} i}花括号a] i]方括号a> i>尖括号a' i'单引号a" i"双引号a` i`反引号at itxml标签

2.操作文本块
iw当前单词aw当前单词及一个空格iW当前字串aW当前字串及一个空格is当前句子as当前句子及一个空格ip当前段落ap当前段落及一个空格

一般来说，d{motion} 命令和 aw、aW, as 和 ap 配合起来使用比较好，而 c{motion} 命令和 iw 及类似的文本对象一起用效果会更好。

