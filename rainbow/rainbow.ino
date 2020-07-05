#include "M5Atom.h"

void setup()
{
    M5.begin(true, false, true);
}

int ptr = 0;

CRGB colors[] = {
  0xff0000,
  0xff8000,
  0xffff00,
  0x80ff00,
  0x00ff00,
  0x00ff80,
  0x00ffff,
  0x0080ff,
  0x0000ff,
  0x8000ff,
  0xff00ff,
  0xff0080
};

void loop()
{
    int i, j, t, x, y, p;
    p = ptr;
    for (i = 0; i < 9; i++) {
      t = 4 - abs(4 - i);
      for (j = 0; j <= t; j++) {
        if (i <= 4) {
          x = j;
          y = t - j;
        }
        else {
          x = (4 - t) + j;
          y = 4 - j;
        }          
        M5.dis.drawpix(x, y, colors[p]);
      }
      p++;
      p = (p == 12) ? 0 : p;
    }
    delay(100);
    ptr++;
    ptr = (ptr == 12) ? 0 : ptr;
}
