#include <gflags/gflags.h>

#include <iostream>

DEFINE_string(name, "wangwang", "my name");

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  std::cout << FLAGS_name << std::endl;

  return 0;
}