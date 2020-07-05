#include "M5Atom.h"
#include <WiFi.h>
#include <time.h>

const char* ssid       = "your_ssid";
const char* password   = "your_pass";

uint8_t nums[10][15] = {
  {
    1, 1, 1,
    1, 0, 1,
    1, 0, 1,
    1, 0, 1,
    1, 1, 1,
  },
  {
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0
  },
  {
    1, 1, 1,
    0, 0, 1,
    1, 1, 1,
    1, 0, 0,
    1, 1, 1
  },
  {
    1, 1, 1,
    0, 0, 1,
    1, 1, 1,
    0, 0, 1,
    1, 1, 1
  },
  {
    1, 0, 1,
    1, 0, 1,
    1, 1, 1,
    0, 0, 1,
    0, 0, 1
  },
  {
    1, 1, 1,
    1, 0, 0,
    1, 1, 1,
    0, 0, 1,
    1, 1, 1
  },
  {
    1, 1, 1,
    1, 0, 0,
    1, 1, 1,
    1, 0, 1,
    1, 1, 1
  },
  {
    1, 1, 1,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1
  },
  {
    1, 1, 1,
    1, 0, 1,
    1, 1, 1,
    1, 0, 1,
    1, 1, 1
  },
  {
    1, 1, 1,
    1, 0, 1,
    1, 1, 1,
    0, 0, 1,
    1, 1, 1
  }
};
uint8_t colon[] = {
  0, 0, 0,
  0, 1, 0,
  0, 0, 0,
  0, 1, 0,
  0, 0, 0
};

uint8_t buf[2 + 9 * 4 * 3 * 5];
int ofs;

void setNum(int pos, int num, int r, int g, int b) {
  int x, y, p, c;

  for (y = 0; y < 5; y++) {
    for (x = 0; x < 3; x++) {
      p = 2 + (pos * 4 + x) * 3 + y * 9 * 4 * 3;
      c = y * 3 + x;
/*
      Serial.print("setNum num = ");
      Serial.print(num);
      Serial.print(", p = ");
      Serial.print(p);
      Serial.print(", nums[c] = ");
      Serial.print(nums[num][c]);
*/
      buf[p] = (nums[num][c] == 1) ? r : 0;
      buf[p + 1] = (nums[num][c] == 1) ? g : 0;
      buf[p + 2] = (nums[num][c] == 1) ? b : 0;
/*
      Serial.print(", buf[p] = ");
      Serial.print(buf[p]);
      Serial.print(", buf[p+1] = ");
      Serial.print(buf[p+1]);
      Serial.print(", buf[p+2] = ");
      Serial.println(buf[p+2]);
*/
    }
  }
}

void setColon(int pos, int r, int g, int b) {
  int x, y, p, c;

  for (y = 0; y < 5; y++) {
    for (x = 0; x < 3; x++) {
      p = 2 + (pos * 4 + x) * 3 + y * 9 * 4 * 3;
      c = y * 3 + x;
/*
      Serial.print("setColon p = ");
      Serial.println(p);
*/
      buf[p] = (colon[c] == 1) ? r : 0;
      buf[p + 1] = (colon[c] == 1) ? g : 0;
      buf[p + 2] = (colon[c] == 1) ? b : 0;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  M5.begin(true, false, true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  configTime(9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
  ofs = 0;
/*
  buf[0] = 9 * 4;
  buf[1] = 5;
  setNum(0, 0, 0xff, 0, 0);
  setNum(1, 1, 0xff, 0, 0);
  setNum(2, 2, 0xff, 0, 0);
  setNum(3, 3, 0xff, 0, 0);
  setNum(4, 4, 0xff, 0, 0);
  setNum(5, 5, 0xff, 0, 0);
  setNum(6, 6, 0xff, 0, 0);
  setNum(7, 7, 0xff, 0, 0);
  setNum(8, 8, 0xff, 0, 0);
*/
}

void loop() {
  struct tm timeInfo;
  memset(buf, 0, sizeof(buf));
  buf[0] = 9 * 4;
  buf[1] = 5;
  getLocalTime(&timeInfo);
/*
  Serial.print("hour = ");
  Serial.print(timeInfo.tm_hour);
  Serial.print(", min = ");
  Serial.print(timeInfo.tm_min);
  Serial.print(", sec = ");
  Serial.println(timeInfo.tm_sec);
*/
  setNum(0, timeInfo.tm_hour / 10, 0xff, 0, 0);
  setNum(1, timeInfo.tm_hour % 10, 0xff, 0, 0);
  setColon(2, 0xff, 0, 0);
  setNum(3, timeInfo.tm_min / 10, 0xff, 0, 0);
  setNum(4, timeInfo.tm_min % 10, 0xff, 0, 0);
  setColon(5, 0xff, 0, 0);
  setNum(6, timeInfo.tm_sec / 10, 0xff, 0, 0);
  setNum(7, timeInfo.tm_sec % 10, 0xff, 0, 0);
  M5.dis.displaybuff(buf, ofs, 0);
  ofs--;
  ofs = (ofs == -1) ? buf[0] - 1 : ofs;
  delay(200);
}
