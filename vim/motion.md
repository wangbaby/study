Vim中进行光标移动的命令是针对不同的操作单位而设计，不同的命令对应不同的操作单位。
在执行Vim光标移动命令时，首先要分清楚是采用哪种操作单位：一个字符、一个句子、一个段落、一行、一屏、一页。
确定操作单位后，需要确定命令重复执行的次数。Vim 光标移动命令的操作对象范围计算公式为：
操作范围 = 操作次数 x 操作单位
例如：5h 命令表示左移 5 个字符，8w 命令右移 8 个单词。

字符移动

f{char}正向移动到下一个char字符上用 ; 和 , 命令相应地正向或反向重复此跳转F{char}反向移动到上一个char字符上t{char}正向移动到下一个char字符之前的一个字符T{char}反向移动到上一个char字符之前的一个字符

位置标记移动

'm设置位置标记，以便快速调回						m{a-zA-Z} 命令会用选定的字母标记当前光标所在位置(参见:h m )。小写位置标记只在每个缓冲区里局部可见，而大写位置标记则全局可见。'命令跳到位置标记所在行，并把光标置于该行第一个非空白字符上;而`命令则把光标移动到设置此位置标记时光标所在之处，也就是说，它同时恢复行、列的位置					mm 和 'm最常用

行级移动

0         移动光标到当前行行首
$         移动光标到当前行行尾
^         移动光标到当前行的第一个非空字符
nG       移动光标到当前文件的第n行
:n       移动光标到当前文件的第n行 (同上)
注：
(1) Vim 的命令中，0 表示行首，$ 表示行尾。可以回顾下Vim文本编辑命令汇总中提到的删除命令，里面就提到了 0 和 $。
(2) 移动光标到当前文件的第 n 行使用的命令 :n 是在vim命令行模式下执行的，所以输入完 :n 后需要按回车键执行命令。

文件首尾移动

gg 或 :0       移动光标到当前文件的第一行
GG 或 :$       移动光标到当前未经的最后一行

单词级移动

w 或 W          移动到下一单词的开头
b 或 B          移动到上一单词的开头
e 或 E          移动到光标所在单词的末尾
ge               反向移动到上一单词尾部
W、B、E命令操作的单词是以空白字符(空格、Tab)分隔的字串。
比如字符串“str1-str2 str3-str4”，对W、B、E命令来说是两个单词，而对w、b、e命令来说则是四个单词。

匹配单词级移动

*        移动光标到匹配光标当前所在单词的下一个单词
#        移动光标到匹配光标当前所在单词的上一个单词

匹配括号移动

%        移动光标到括号左半部分( 包括(、{、[ )对应右半匹配部分( )、}、] )

段落级移动

}       移动光标到当前段落的末尾
{       移到光标到当前段落的开头

屏幕级移动

H       移动光标到屏幕的第一行
M       移动光标到屏幕的中间一行
L       移动光标到屏幕的最后一行

翻页

Ctrl + f       向前滚动一页
Ctrl + b       向后滚动一页
Ctrl + u       向前滚动半页
Ctrl + d       向后滚动半页