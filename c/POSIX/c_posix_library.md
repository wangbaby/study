# C POSIX library

The C POSIX library is a specification of a C standard library for POSIX systems. It was developed at the same time as the ANSI C standard. Some effort was made to make POSIX compatible with standard C; POSIX includes additional functions to those introduced in standard C.

# unistd.h

[reference](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html)

Various essential POSIX functions and constants

On Unix-like systems, the interface defined by unistd.h is typically made up largely of system call wrapper functions such as fork, pipe and I/O primitives (read, write, close, etc.).

# pthread.h

[reference](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html)

Defines an API for creating and manipulating POSIX threads

# fcntl.h

[reference](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/fcntl.h.html)

File opening, locking and other operations

# semaphore.h

[reference](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/semaphore.h.html)

POSIX semaphores

Semaphore is a synchronization mechanism. In more words, semaphores are a technique for coordinating or synchronizing activities in which multiple processes compete for the same resources. There are 2 types of semaphores: Binary semaphores & Counting semaphores.

Binary Semaphores: Only two states 0 & 1, i.e., locked/unlocked or available/unavailable, Mutex implementation.
Counting Semaphores: Semaphores which allow arbitrary resource count called counting semaphores.
Here, we will see the POSIX style semaphore. POSIX semaphore calls are much simpler than the System V semaphore calls. However, System V semaphores are more widely available, particularly on older Unix-like systems. POSIX semaphores have been available on Linux systems post version 2.6 that use Glibc.

There are two types of POSIX semaphores: named & unnamed. The named semaphore(which internally implemented using shared memory) generally used between processes. As it creates shared memory system-wide & can use in multiple processes. But if you have threads only then, the unnamed semaphore will be the best choice.

# sys/types.h

[reference](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_types.h.html#tag_13_65)

data types

# sys/wait.h

[reference](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_wait.h.html#tag_13_69)

declarations for waiting
