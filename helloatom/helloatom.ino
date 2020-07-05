#include "M5Atom.h"
#include "hello.c"

int ofs = 0;

void setup() {
  M5.begin(true, false, true);
}

void loop() {
  M5.dis.displaybuff((uint8_t *) image_hello, ofs, 0);
  ofs--;
  ofs = (ofs == -1) ? image_hello[0] - 1 : ofs;
  delay(100);
}
