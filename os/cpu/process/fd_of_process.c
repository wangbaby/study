#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  sleep(600);

  printf("hello from stdout!");

  return EXIT_SUCCESS;
}