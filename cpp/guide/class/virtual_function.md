
使用gdb探索 C++ 虚函数表 —— 单继承

以下内容均是在下列环境讨论的
Ubuntu 19.04 64bit系统
gcc 8.3.0，即Itanium ABI
gdb 8.2.91
Python 3.7.3


单继承没有覆盖

class A {
public:
    A() : ma{-1} {}
    virtual ~A() = default;
    virtual void va1() {}
    virtual void va2() {}
    void fa1() {}
    long ma;
};

class B : public A {
public:
    B() : mb{-2} {}
    virtual ~B() = default;
    virtual void vb1() {}
    virtual void vb2() {}
    void fb1() {}
    long mb;
};

class C : public B {
public:
    C() : mc{-3} {}
    virtual ~C() = default;
    virtual void vc1() {}
    virtual void vc2() {}
    void fc1() {}
    long mc;
};

int main() {
    A a;
    B b;
    C c;
    return 0;
}

在gdb调试上述代码
// 检查a的内存布局
(gdb) checksymbol &a sizeof(a)
debug info, addr is: 0x7fffffffde20, len is: 16
0x7fffffffde20: 	 0x0000555555557d50 	 vtable for A + 16
0x7fffffffde28: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.

// 检查a的虚函数表
(gdb) checksymbol *(long*)&a-16 48
debug info, addr is: 93824992247104, len is: 48
0x555555557d40 <vtable for A>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.
0x555555557d48 <vtable for A+8>: 	 0x0000555555557da0 	 typeinfo for A
0x555555557d50 <vtable for A+16>: 	 0x0000555555555206 	 A::~A()
0x555555557d58 <vtable for A+24>: 	 0x0000555555555220 	 A::~A()
0x555555557d60 <vtable for A+32>: 	 0x00005555555551ee 	 A::va1()
0x555555557d68 <vtable for A+40>: 	 0x00005555555551fa 	 A::va2()

只有虚函数才会出现在虚函数表中。
类实例的前8字节是指向虚函数表的指针，但是注意它并没有指向虚函数表的起始地址，后面是类成员。
虚函数表第一个8字节是top_offset，在单继承中没有什么作用，均是0。
第二个8字节是用于支持RTTI的type info指针，就算编译时禁用RTTI，虚函数表还是有这一项，只是内容没意义
第三和第四个8字节是虚析构函数的指针，至于为什么是两个，不在本篇讨论范围，参见文末Ref。
剩下的就是各个虚函数的指针
所以一个有虚函数的普通类的结构
内存结构：
地址内容含义0x7fffffffde200x0000555555557d50vtable for A + 16 虚函数表指针0x7fffffffde280xffffffffffffffffA::ma
虚函数表结构：
地址内容含义0x555555557d400x0000000000000000top_offset0x555555557d480x0000555555557da0typeinfo for A0x555555557d500x0000555555555206A::~A()0x555555557d580x0000555555555220A::~A()0x555555557d600x00005555555551eeA::va1()0x555555557d680x00005555555551faA::va2()

(gdb) checksymbol &b sizeof(b)
debug info, addr is: 0x7fffffffde30, len is: 24
0x7fffffffde30: 	 0x0000555555557d10 	 vtable for B + 16
0x7fffffffde38: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.
0x7fffffffde40: 	 0xfffffffffffffffe 	 No symbol matches 0xfffffffffffffffe.

(gdb) checksymbol *(long*)&b-16 64
debug info, addr is: 93824992247040, len is: 64
0x555555557d00 <vtable for B>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.
0x555555557d08 <vtable for B+8>: 	 0x0000555555557d88 	 typeinfo for B
0x555555557d10 <vtable for B+16>: 	 0x000055555555529a 	 B::~B()
0x555555557d18 <vtable for B+24>: 	 0x00005555555552c4 	 B::~B()
0x555555557d20 <vtable for B+32>: 	 0x00005555555551ee 	 A::va1()
0x555555557d28 <vtable for B+40>: 	 0x00005555555551fa 	 A::va2()
0x555555557d30 <vtable for B+48>: 	 0x0000555555555282 	 B::vb1()
0x555555557d38 <vtable for B+56>: 	 0x000055555555528e 	 B::vb2()
类B的结构和类A很接近，只是多了继承自类A的虚函数
内存结构：
地址内容含义0x7fffffffde300x0000555555557d10vtable for B + 16 虚函数表指针0x7fffffffde380xffffffffffffffffA::ma0x7fffffffde400xfffffffffffffffeB::mb
虚函数表结构：
地址内容含义0x555555557d000x0000000000000000top_offset0x555555557d080x0000555555557d88typeinfo for B0x555555557d100x000055555555529aB::~B()0x555555557d180x00005555555552c4B::~B()0x555555557d200x00005555555551eeA::va1()0x555555557d280x00005555555551faA::va2()0x555555557d300x0000555555555282B::vb1()0x555555557d380x000055555555528eB::vb2()
从类A和类B的虚函数表地址和符号名可以看出来，这两个不是同一张表，也不存在公共的部分，只不过有一部分内容相同而已。
类B的虚函数表前面部分的布局和类A的虚函数表布局一致，这样只要虚函数表里虚函数地址的顺序确定了（编译期），运行时就可以根据offset来调用对应的函数。
(gdb) checksymbol &c sizeof(c)
debug info, addr is: 0x7fffffffde50, len is: 32
0x7fffffffde50: 	 0x0000555555557cc0 	 vtable for C + 16
0x7fffffffde58: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.
0x7fffffffde60: 	 0xfffffffffffffffe 	 No symbol matches 0xfffffffffffffffe.
0x7fffffffde68: 	 0xfffffffffffffffd 	 No symbol matches 0xfffffffffffffffd.

(gdb) checksymbol *(long*)&c-16 80
debug info, addr is: 93824992246960, len is: 80
0x555555557cb0 <vtable for C>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.
0x555555557cb8 <vtable for C+8>: 	 0x0000555555557d70 	 typeinfo for C
0x555555557cc0 <vtable for C+16>: 	 0x000055555555533e 	 C::~C()
0x555555557cc8 <vtable for C+24>: 	 0x0000555555555368 	 C::~C()
0x555555557cd0 <vtable for C+32>: 	 0x00005555555551ee 	 A::va1()
0x555555557cd8 <vtable for C+40>: 	 0x00005555555551fa 	 A::va2()
0x555555557ce0 <vtable for C+48>: 	 0x0000555555555282 	 B::vb1()
0x555555557ce8 <vtable for C+56>: 	 0x000055555555528e 	 B::vb2()
0x555555557cf0 <vtable for C+64>: 	 0x0000555555555326 	 C::vc1()
0x555555557cf8 <vtable for C+72>: 	 0x0000555555555332 	 C::vc2()

类C的结构和上面是一致的

单继承有覆盖
class A {
public:
    A() : ma{-1} {}
    virtual ~A() = default;
    virtual void va1() {}
    virtual void va2() {}
    void fa1() {}
    long ma;
};

class B : public A {
public:
    B() : mb{-2} {}
    virtual ~B() = default;
    virtual void vb1() {}
    virtual void vb2() {}
    virtual void va2() {}
    void fb1() {}
    long mb;
};

class C : public B {
public:
    C() : mc{-3} {}
    virtual ~C() = default;
    virtual void vb1() {}
    virtual void vc2() {}
    virtual void vc1() {}
    virtual void va2() {}
    void fc1() {}
    long mc;
};

int main() {
    A a;
    B b;
    C c;
    return 0;
}

在gdb里调试
(gdb) checksymbol &a sizeof(a)
debug info, addr is: 0x7fffffffde20, len is: 16
0x7fffffffde20: 	 0x0000555555557d50 	 vtable for A + 16
0x7fffffffde28: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.

(gdb) checksymbol *(long*)&a-16 48
debug info, addr is: 93824992247104, len is: 48
0x555555557d40 <vtable for A>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.
0x555555557d48 <vtable for A+8>: 	 0x0000555555557da0 	 typeinfo for A
0x555555557d50 <vtable for A+16>: 	 0x0000555555555206 	 A::~A()
0x555555557d58 <vtable for A+24>: 	 0x0000555555555220 	 A::~A()
0x555555557d60 <vtable for A+32>: 	 0x00005555555551ee 	 A::va1()
0x555555557d68 <vtable for A+40>: 	 0x00005555555551fa 	 A::va2()

类A和没有覆盖时一样
(gdb) checksymbol &b sizeof(b)
debug info, addr is: 0x7fffffffde30, len is: 24
0x7fffffffde30: 	 0x0000555555557d10 	 vtable for B + 16
0x7fffffffde38: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.
0x7fffffffde40: 	 0xfffffffffffffffe 	 No symbol matches 0xfffffffffffffffe.

(gdb) checksymbol *(long*)&b-16 64
debug info, addr is: 93824992247040, len is: 64
0x555555557d00 <vtable for B>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.
0x555555557d08 <vtable for B+8>: 	 0x0000555555557d88 	 typeinfo for B
0x555555557d10 <vtable for B+16>: 	 0x00005555555552a6 	 B::~B()
0x555555557d18 <vtable for B+24>: 	 0x00005555555552d0 	 B::~B()
0x555555557d20 <vtable for B+32>: 	 0x00005555555551ee 	 A::va1()
0x555555557d28 <vtable for B+40>: 	 0x000055555555529a 	 B::va2()
0x555555557d30 <vtable for B+48>: 	 0x0000555555555282 	 B::vb1()
0x555555557d38 <vtable for B+56>: 	 0x000055555555528e 	 B::vb2()

类B覆盖了类A的va2函数, 内存布局和没有覆盖时比没有变化 虚函数表有变化

整个虚函数表每个函数的顺序没有改变，只是被覆盖的函数的地址变成了派生类函数的地址。当我们通过基类指针调用va2时，根据offset选到的就是B::va2，也就实现了多态。
(gdb) checksymbol &c sizeof(c)
debug info, addr is: 0x7fffffffde50, len is: 32
0x7fffffffde50: 	 0x0000555555557cc0 	 vtable for C + 16
0x7fffffffde58: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.
0x7fffffffde60: 	 0xfffffffffffffffe 	 No symbol matches 0xfffffffffffffffe.
0x7fffffffde68: 	 0xfffffffffffffffd 	 No symbol matches 0xfffffffffffffffd.

(gdb) checksymbol *(long*)&c-16 80
debug info, addr is: 93824992246960, len is: 80
0x555555557cb0 <vtable for C>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.
0x555555557cb8 <vtable for C+8>: 	 0x0000555555557d70 	 typeinfo for C
0x555555557cc0 <vtable for C+16>: 	 0x0000555555555362 	 C::~C()
0x555555557cc8 <vtable for C+24>: 	 0x000055555555538c 	 C::~C()
0x555555557cd0 <vtable for C+32>: 	 0x00005555555551ee 	 A::va1()
0x555555557cd8 <vtable for C+40>: 	 0x0000555555555356 	 C::va2()
0x555555557ce0 <vtable for C+48>: 	 0x0000555555555332 	 C::vb1()
0x555555557ce8 <vtable for C+56>: 	 0x000055555555528e 	 B::vb2()
0x555555557cf0 <vtable for C+64>: 	 0x000055555555533e 	 C::vc2()
0x555555557cf8 <vtable for C+72>: 	 0x000055555555534a 	 C::vc1()

类C的情况和上面的结论一致

多继承没有覆盖
12345678910111213141516171819202122232425262728293031323334353637class A {public:    A() : ma{-1}, maa{-10} {}    virtual ~A() = default;    virtual void va1() {}    virtual void va2() {}    void fa1() {}    long ma;    long maa;};class B {public:    B() : mb{-2} {}    virtual ~B() = default;    virtual void vb1() {}    virtual void vb2() {}    void fb1() {}    long mb;};class C : public A, public B {public:    C() : mc{-4} {}    virtual ~C() = default;    virtual void vc2() {}    virtual void vc1() {}    void fc1() {}    long mc;};int main() {    A a;    B b;    C c;    return 0;}
在gdb调试上述代码
1234567891011121314(gdb) checksymbol &a sizeof(a)debug info, addr is: 0x7fffffffde20, len is: 240x7fffffffde20: 	 0x0000555555557d38 	 vtable for A + 160x7fffffffde28: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.0x7fffffffde30: 	 0xfffffffffffffff6 	 No symbol matches 0xfffffffffffffff6.(gdb) checksymbol *(long*)&a-16 48debug info, addr is: 93824992247080, len is: 480x555555557d28 <vtable for A>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.0x555555557d30 <vtable for A+8>: 	 0x0000555555557da0 	 typeinfo for A0x555555557d38 <vtable for A+16>: 	 0x0000555555555250 	 A::~A()0x555555557d40 <vtable for A+24>: 	 0x000055555555526a 	 A::~A()0x555555557d48 <vtable for A+32>: 	 0x00005555555551fa 	 A::va1()0x555555557d50 <vtable for A+40>: 	 0x0000555555555206 	 A::va2()
12345678910111213(gdb) checksymbol &b sizeof(b)debug info, addr is: 0x7fffffffde10, len is: 160x7fffffffde10: 	 0x0000555555557d08 	 vtable for B + 160x7fffffffde18: 	 0xfffffffffffffffe 	 No symbol matches 0xfffffffffffffffe.(gdb) checksymbol *(long*)&b-16 48debug info, addr is: 93824992247032, len is: 480x555555557cf8 <vtable for B>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.0x555555557d00 <vtable for B+8>: 	 0x0000555555557d90 	 typeinfo for B0x555555557d08 <vtable for B+16>: 	 0x0000555555555296 	 B::~B()0x555555557d10 <vtable for B+24>: 	 0x00005555555552b0 	 B::~B()0x555555557d18 <vtable for B+32>: 	 0x0000555555555238 	 B::vb1()0x555555557d20 <vtable for B+40>: 	 0x0000555555555244 	 B::vb2()
类A、B没有继承任何类，结构比较简单，下面看类C
12345678910111213141516171819202122232425(gdb) checksymbol &c sizeof(c)debug info, addr is: 0x7fffffffde40, len is: 480x7fffffffde40: 	 0x0000555555557c98 	 vtable for C + 160x7fffffffde48: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.0x7fffffffde50: 	 0xfffffffffffffff6 	 No symbol matches 0xfffffffffffffff6.0x7fffffffde58: 	 0x0000555555557cd8 	 vtable for C + 800x7fffffffde60: 	 0xfffffffffffffffe 	 No symbol matches 0xfffffffffffffffe.0x7fffffffde68: 	 0xfffffffffffffffc 	 No symbol matches 0xfffffffffffffffc.(gdb) checksymbol *(long*)&c-16 112debug info, addr is: 93824992246920, len is: 1120x555555557c88 <vtable for C>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.0x555555557c90 <vtable for C+8>: 	 0x0000555555557d58 	 typeinfo for C0x555555557c98 <vtable for C+16>: 	 0x0000555555555348 	 C::~C()0x555555557ca0 <vtable for C+24>: 	 0x0000555555555396 	 C::~C()0x555555557ca8 <vtable for C+32>: 	 0x00005555555551fa 	 A::va1()0x555555557cb0 <vtable for C+40>: 	 0x0000555555555206 	 A::va2()0x555555557cb8 <vtable for C+48>: 	 0x0000555555555330 	 C::vc2()0x555555557cc0 <vtable for C+56>: 	 0x000055555555533c 	 C::vc1()0x555555557cc8 <vtable for C+64>: 	 0xffffffffffffffe8 	 No symbol matches 0xffffffffffffffe8.0x555555557cd0 <vtable for C+72>: 	 0x0000555555557d58 	 typeinfo for C0x555555557cd8 <vtable for C+80>: 	 0x0000555555555390 	 non-virtual thunk to C::~C()0x555555557ce0 <vtable for C+88>: 	 0x00005555555553c1 	 non-virtual thunk to C::~C()0x555555557ce8 <vtable for C+96>: 	 0x0000555555555238 	 B::vb1()0x555555557cf0 <vtable for C+104>: 	 0x0000555555555244 	 B::vb2()
内存结构：
地址内容含义0x7fffffffde400x0000555555557c98vtable for C + 16 虚函数表指针0x7fffffffde480xffffffffffffffffA::ma0x7fffffffde500xfffffffffffffff6A::maa0x7fffffffde580x0000555555557cd8vtable for C + 80 虚函数表指针0x7fffffffde600xfffffffffffffffeB::mb0x7fffffffde680xfffffffffffffffcC::mc
类成员还是按照A、B、C排列，在A、B类成员间多了一个虚函数表指针。vtable for C + 16用于类A和C，vtable for C + 80用于类B。
虚函数表结构：
地址内容含义0x555555557c88 [vtable for C]0x0000000000000000top_offset0x555555557c90 [vtable for C+8]0x0000555555557d58typeinfo for C0x555555557c98 [vtable for C+16]0x0000555555555348C::~C()0x555555557ca0 [vtable for C+24]0x0000555555555396C::~C()0x555555557ca8 [vtable for C+32]0x00005555555551faA::va1()0x555555557cb0 [vtable for C+40]0x0000555555555206A::va2()0x555555557cb8 [vtable for C+48]0x0000555555555330C::vc2()0x555555557cc0 [vtable for C+56]0x000055555555533cC::vc1()0x555555557cc8 [vtable for C+64]0xffffffffffffffe8top_offset 值为-240x555555557cd0 [vtable for C+72]0x0000555555557d58typeinfo for C0x555555557cd8 [vtable for C+80]0x0000555555555390non-virtual thunk to C::~C()0x555555557ce0 [vtable for C+88]0x00005555555553c1non-virtual thunk to C::~C()0x555555557ce8 [vtable for C+96]0x0000555555555238B::vb1()0x555555557cf0 [vtable for C+104]0x0000555555555244B::vb2()
这里能看到有两个类似单继承中的虚函数表结构：vtable for C 0～63和vtable for C 64～111
多继承有覆盖
123456789101112131415161718192021222324252627282930313233343536373839class A {public:    A() : ma{-1}, maa{-10} {}    virtual ~A() = default;    virtual void va1() {}    virtual void va2() {}    void fa1() {}    long ma;    long maa;};class B {public:    B() : mb{-2} {}    virtual ~B() = default;    virtual void vb1() {}    virtual void vb2() {}    void fb1() {}    long mb;};class C : public A, public B {public:    C() : mc{-4} {}    virtual ~C() = default;    virtual void vc2() {}    virtual void vc1() {}    virtual void vb1() {}    virtual void va2() {}    void fc1() {}    long mc;};int main() {    A a;    B b;    C c;    return 0;}
类C覆盖了类A的va2和类B的vb1方法。
1234567891011121314(gdb) checksymbol &a sizeof(a)debug info, addr is: 0x7fffffffde20, len is: 240x7fffffffde20: 	 0x0000555555557d38 	 vtable for A + 160x7fffffffde28: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.0x7fffffffde30: 	 0xfffffffffffffff6 	 No symbol matches 0xfffffffffffffff6.(gdb) checksymbol *(long*)&a-16 48debug info, addr is: 93824992247080, len is: 480x555555557d28 <vtable for A>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.0x555555557d30 <vtable for A+8>: 	 0x0000555555557da0 	 typeinfo for A0x555555557d38 <vtable for A+16>: 	 0x0000555555555250 	 A::~A()0x555555557d40 <vtable for A+24>: 	 0x000055555555526a 	 A::~A()0x555555557d48 <vtable for A+32>: 	 0x00005555555551fa 	 A::va1()0x555555557d50 <vtable for A+40>: 	 0x0000555555555206 	 A::va2()
12345678910111213(gdb) checksymbol &b sizeof(b)debug info, addr is: 0x7fffffffde10, len is: 160x7fffffffde10: 	 0x0000555555557d08 	 vtable for B + 160x7fffffffde18: 	 0xfffffffffffffffe 	 No symbol matches 0xfffffffffffffffe.(gdb) checksymbol *(long*)&b-16 48debug info, addr is: 93824992247032, len is: 480x555555557cf8 <vtable for B>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.0x555555557d00 <vtable for B+8>: 	 0x0000555555557d90 	 typeinfo for B0x555555557d08 <vtable for B+16>: 	 0x0000555555555296 	 B::~B()0x555555557d10 <vtable for B+24>: 	 0x00005555555552b0 	 B::~B()0x555555557d18 <vtable for B+32>: 	 0x0000555555555238 	 B::vb1()0x555555557d20 <vtable for B+40>: 	 0x0000555555555244 	 B::vb2()
类A、B和之前一样没什么变化，下面看类C
12345678(gdb) checksymbol &c sizeof(c)debug info, addr is: 0x7fffffffde40, len is: 480x7fffffffde40: 	 0x0000555555557c90 	 vtable for C + 160x7fffffffde48: 	 0xffffffffffffffff 	 No symbol matches 0xffffffffffffffff.0x7fffffffde50: 	 0xfffffffffffffff6 	 No symbol matches 0xfffffffffffffff6.0x7fffffffde58: 	 0x0000555555557cd8 	 vtable for C + 880x7fffffffde60: 	 0xfffffffffffffffe 	 No symbol matches 0xfffffffffffffffe.0x7fffffffde68: 	 0xfffffffffffffffc 	 No symbol matches 0xfffffffffffffffc.
类C的内存布局和之前一致
1234567891011121314151617(gdb) checksymbol *(long*)&c-16 120debug info, addr is: 93824992246912, len is: 1200x555555557c80 <vtable for C>: 	 0x0000000000000000 	 No symbol matches 0x0000000000000000.0x555555557c88 <vtable for C+8>: 	 0x0000555555557d58 	 typeinfo for C0x555555557c90 <vtable for C+16>: 	 0x0000555555555366 	 C::~C()0x555555557c98 <vtable for C+24>: 	 0x00005555555553b4 	 C::~C()0x555555557ca0 <vtable for C+32>: 	 0x00005555555551fa 	 A::va1()0x555555557ca8 <vtable for C+40>: 	 0x000055555555535a 	 C::va2()0x555555557cb0 <vtable for C+48>: 	 0x0000555555555330 	 C::vc2()0x555555557cb8 <vtable for C+56>: 	 0x000055555555533c 	 C::vc1()0x555555557cc0 <vtable for C+64>: 	 0x0000555555555348 	 C::vb1()0x555555557cc8 <vtable for C+72>: 	 0xffffffffffffffe8 	 No symbol matches 0xffffffffffffffe8.0x555555557cd0 <vtable for C+80>: 	 0x0000555555557d58 	 typeinfo for C0x555555557cd8 <vtable for C+88>: 	 0x00005555555553ae 	 non-virtual thunk to C::~C()0x555555557ce0 <vtable for C+96>: 	 0x00005555555553df 	 non-virtual thunk to C::~C()0x555555557ce8 <vtable for C+104>: 	 0x0000555555555353 	 non-virtual thunk to C::vb1()0x555555557cf0 <vtable for C+112>: 	 0x0000555555555244 	 B::vb2()
虚函数表结构：
地址内容含义0x555555557c80 [vtable for C]0x0000000000000000top_offset0x555555557c88 [vtable for C+8]0x0000555555557d58typeinfo for C0x555555557c90 [vtable for C+16]0x0000555555555366C::~C()0x555555557c98 [vtable for C+24]0x00005555555553b4C::~C()0x555555557ca0 [vtable for C+32]0x00005555555551faA::va1()0x555555557ca8 [vtable for C+40]0x000055555555535aC::va2()0x555555557cb0 [vtable for C+48]0x0000555555555330C::vc2()0x555555557cb8 [vtable for C+56]0x000055555555533cC::vc1()0x555555557cc0 [vtable for C+64]0x0000555555555348C::vb1()0x555555557cc8 [vtable for C+72]0xffffffffffffffe8top_offset，值为-240x555555557cd0 [vtable for C+80]0x0000555555557d58typeinfo for C0x555555557cd8 [vtable for C+88]0x00005555555553aenon-virtual thunk to C::~C()0x555555557ce0 [vtable for C+96]0x00005555555553dfnon-virtual thunk to C::~C()0x555555557ce8 [vtable for C+104]0x0000555555555353non-virtual thunk to C::vb1()0x555555557cf0 [vtable for C+112]0x0000555555555244B::vb2()
vtable for C 0～47和类A的虚函数表布局一致，当作类A操作也可以，所以被覆盖的va2指针直接替换为C::va2的指针。
但是，vtable for C 0～XX无法形成和类B的虚函数表相同的布局，所以编译器在vtable for C 72～119构造了与类B相同布局的虚函数表。
被覆盖的vb1函数指针被“non-virtual thunk to C::vb1()”函数指针替换，什么是“non-virtual thunk”？
先看下类型转换的结果
12(gdb) p static_cast<B*>(&c)$6 = (B *) 0x7fffffffde58
转换为B*后和&c的值并不相同，而是c的第二个虚函数表指针的地址“vtable for C + 88”
123void foo(B* f) {    f->vb1();}
函数void foo(B*)接受类B的指针，如果传入一个类c的实例，首先会进行类型转换，这时this指针指向c的第二个虚函数表指针“vtable for C + 88”。对vb1方法的调用应该是执行类C的vb1函数，但是此时的this指针对于类C的vb1函数是不对的。“non-virtual thunk to C::vb1()”就是用来修正this指针并调用C::vb1，它通过top_offset将this修改到正确的值“vtable for C + 16”。
12345(gdb) disassemble 0x0000555555555353Dump of assembler code for function _ZThn24_N1C3vb1Ev:   0x0000555555555353 <+0>:	sub    $0x18,%rdi   0x0000555555555357 <+4>:	jmp    0x555555555348 <C::vb1()>End of assembler dump.
