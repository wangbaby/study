
# segmentation_fault

段错误会触发SIGSEGV信号，通过man 7 signal，可以看到SIGSEGV默认的handler会打印段错误出错信息，并产生core文件，由此我们可以借助于程序异常退出时生成的core文件中的调试信息，使用gdb工具来调试程序中的段错误