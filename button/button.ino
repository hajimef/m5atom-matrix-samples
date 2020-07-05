#include "M5Atom.h"

int ctr = 0;
void setup() {
  M5.begin(true, false, true);
}

void loop() {
  int i, x, y;
  
  if (M5.Btn.wasPressed()) {
    ctr++;
    ctr %= 26;
    for (i = 0; i < 25; i++) {
      x = i % 5;
      y = i / 5;
      if (i < ctr) {
        M5.dis.drawpix(x, y, 0xffffff);
      }
      else {
        M5.dis.drawpix(x, y, 0x000000);
      }
    }
  }
  delay(50);
  M5.update();
}
