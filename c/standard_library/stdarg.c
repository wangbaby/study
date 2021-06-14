#include <stdarg.h>
#include <stdio.h>

void print(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  while (*fmt != '\0') {
    if (*fmt == 'd') {
      int i = va_arg(args, int);
      printf("%d\n", i);
    } else if (*fmt == 'c') {
      int c = va_arg(args, int);
      printf("%c\n", c);
    } else if (*fmt == 'f') {
      double f = va_arg(args, double);
      printf("%.2f\n", f);
    }

    fmt++;
  }

  va_end(args);
}

int main() {
  print("dcff", 1, 'a', 1.99, 2.45);

  return 0;
}