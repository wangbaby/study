/**
 * The pid_t data type represents process IDs. You can get the process ID of a
 * process by calling getpid. The function getppid returns the process ID of the
 * parent of the current process (this is also known as the parent process ID).
 *
 * Your program should include the header files `unistd.h' and `sys/types.h' to
 * use these functions.
 *
 * Data Type: pid_t
 * The pid_t data type is a signed integer type which is capable of representing
 * a process ID. In the GNU library, this is an int.
 *
 * Function: pid_t getpid(void)
 * The getpid function returns the process ID of the current process.
 *
 * Function: pid_t getppid (void)
 * The getppid function returns the process ID of the parent of the current
 * process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t child = getpid();
  pid_t parent = getppid();

  printf("child pid is %d, parent pid is %d\n", child, parent);

  return EXIT_SUCCESS;
}