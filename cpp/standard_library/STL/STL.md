# STL 版本

## SGI STL

STL 之父 Alexander Stepanov 离开 HP 之后就去了 SGI（Silicon Graphics Computer System, Inc），然后和 Matt Austern 这些 STL 大牛一起搞了 SGI STL。它也是 HP STL 的一个继承版本。它属于开放源码，因此你可以修改和销售它。SGI STL 被 GCC（linux 下的 C++编译器）所采用，你可以在 GCC 的 Include 子目录下找到所有头文件。由于 GCC 对 C++语言标准的支持很好，SGI STL 在 linux 平台上的性能相当出色。此外，其源代码的可读性也很好。

## PJ STL

Visual C++里的 STL，作者 P.J. Plauger，所以一般也说 pj stl。P. J. Plauger STL 属于个人作品，由 P. J. Plauger 本人实现，是 HP STL 的一个继承版本，因此在其所有头文件中都含有 HP STL 的相关声明，同时还有 P. J. Plauger 本人的版权声明。其实这份 STL 是他公司的产品，不过他跟 MS 的关系实在是好得有点古怪，所以虽然 Plauger 水平极高，很多人却看他不惯。当然，据说 Plauger 除了钱以外也看不惯其他东西，所以 Plauger 虽然称不上声名狼藉，也没有什么好名声。因为 VC 6.0 在模板处理方面过于白痴（7.0/7.1 以后就没事了，毕竟 Lippman 出马），所以 pj stl 实在写得辛苦，也难为 Plauger 了。

## HP STL

HP STL 是所有其它 STL 实现版本的根源。它是 STL 之父 Alexander Stepanov 在惠普的 Palo Alto 实验室工作时，和 Meng Lee 共同完成的，是第一个 STL 的实现版本。这个 STL 是开放源码的，所以它允许任何人免费使用、复制、修改、发布和销售该软件和相关文档，前提是必须在所有相关文件中加入 HP STL 的版本信息和授权信息。现在已经很少直接使用这个版本的 STL 了。

## Rouge Wave STL

Rouge Wave STL 是由 Rouge Wave 公司实现的，也是 HP STL 的一个继承版本，除了 HP STL 的相关声明之外，还有 Rouge Wave 公司的版权声明。同时，它也不是开放源码的，因此无法修改和销售。该版本被 Borland C++ Builder 所采用
