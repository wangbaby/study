#include <stdio.h>
#include <unistd.h>

int main() {
  // getcwd
  char buffer[512];
  getcwd(buffer, 512);
  printf("%s\n", buffer);

  // File descriptor : FD
  // STDIN_FILENO
  // STDOUT_FILENO
  // STDERR_FILENO

  return 0;
}