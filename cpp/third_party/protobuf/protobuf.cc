#include <fstream>

#include "example.pb.h"

using namespace std;

int main() {
  // Set data
  example::Person msg;
  msg.set_id(1234);
  msg.set_name("John Doe");
  msg.set_email("jdoe@example.com");

  // Serialization
  fstream output("./Person.bin", ios::out | ios::binary);
  msg.SerializePartialToOstream(&output);
  output.close();

  // Deserialization
  example::Person msg1;
  fstream input("./Person.bin", ios::in | ios::binary);
  msg1.ParseFromIstream(&input);
  input.close();

  // Get data
  cout << msg1.id() << endl;     // 1234
  cout << msg1.name() << endl;   // John Doe
  cout << msg1.email() << endl;  // jdoe@example.com

  return 0;
}