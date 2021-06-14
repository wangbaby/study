一般情况下，我们在链接一个（文件名为 libxxx.so 或 libxxx.a 等的）库时，会使用-lxxx 的方式；在 Linux 中要用到多线程时，需要链接 pthread 库，按照惯例，我们应该使用-lpthread 的方式来进行链接；但是，通过日常的观察，我发现很多开源代码都是使用了-pthread 参数，而非使用-lpthread，这是为什么呢？
一通 Google 后，总算找到一些线索：
为了可移植性：在 Linux 中，pthread 是作为一个单独的库存在的（libpthread.so），但是在其他 Unix 变种中却不一定，比如在 FreeBSD 中是没有单独的 pthread 库的，因此在 FreeBSD 中不能使用-lpthread 来链接 pthread，而使用-pthread 则不会存在这个问题，因为 FreeBSD 的编译器能正确将-pthread 展开为该系统下的依赖参数。同样道理，其他不同的变种也会有这样那样的区别，如果使用-lpthread，则可能在移植到其他 Unix 变种中时会出现问题，为了保持较高的可移植性，我们最好还是使用-pthread（尽管这种做法未被接纳成为 C 标准，但已基本是事实标准）。
添加额外的标志：在多数系统中，-pthread 会被展开为“-D_REENTRANT -lpthread”，即是除了链接 pthread 库外，还先定义了宏\_REENTRANT。定义这个宏的目的，是为了打开系统头文件中的各种多线程支持分支。比如，我们常常使用的错误码标志 errno，如果没有定义\_REENTRANT，则实现为一个全局变量；若是定义了\_REENTRANT，则会实现为每线程独有，从而避免线程竞争错误。
