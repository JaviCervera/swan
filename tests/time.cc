#include "../time"
#include "../console"

using namespace swan;

int main() {
  console::writeln(str::fromnumber(time::millisecs()));
  time::delay(1000);
  console::writeln(str::fromnumber(time::millisecs()));
}
