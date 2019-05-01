#include "FastLED.h"            // 此示例程序需要使用FastLED库

#define NUM_LEDS 26             // LED灯珠数量
#define LED 8                // Arduino输出控制信号引脚

#define P0 A0
#define P1 A1
#define P2 A2
#define P3 A3

#define LED_TYPE WS2812         // LED灯带型号
#define COLOR_ORDER GRB         // RGB灯珠中红色、绿色、蓝色LED的排列顺序

uint8_t max_bright = 255;       // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高
CRGB leds[NUM_LEDS];            // 建立光带leds_t0

void setup() {
  pinMode(P0, INPUT);
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(P3, INPUT);

  LEDS.addLeds<LED_TYPE, LED, COLOR_ORDER>(leds, NUM_LEDS);  // 初始化光带
  FastLED.setBrightness(max_bright);                        // 设置光带亮度
}

void loop() {
  CRGB car = CRGB(253, 175, 17);
  CRGB alpay = CRGB(32, 165, 222);
  CRGB wepay = CRGB(64, 175, 54);
  switch (sig2num()) {
    case 0:
      fill_dark();
      break;
    case 1:
      begin_car(car);
      break;
    case 2:
      go_car(car);
      break;
    case 3:
      sea_car(CRGB::Red, CRGB::Blue);
      sea_car(CRGB::Blue, CRGB::Red);
      break;
    case 4:
      sea_boat();
      break;
    case 5:
      wifi(CRGB(125, 62, 0), CRGB(45, 110, 0));
      break;
    case 6:
      pay(alpay);
      break;
    case 7:
      pay(wepay);
      break;
    case 8:
      quark();
      break;
    case 9:
      earth();
      break;
    case 10:
      cloud();
      break;
    case 11:
      farm(CRGB(255, 135, 0));
      break;
    default:
      fill_dark();
      break;
  }
}

int sig2num() {
  return digitalRead(P0) + 2 * digitalRead(P1) + 4 * digitalRead(P2) + 8 * digitalRead(P3);
}

void fill_dark() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void begin_car(CRGB color) {
  for (int i = 12; i >= 0; i--) {
    leds[i] = color;
    leds[25 - i] = color;
    FastLED.show();
    delay(30);
  }
}

void go_car(CRGB color) {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  while (sig2num() == 2) {
    for (int i = 12; i >= 3; i -= 3) {
      leds[i] = color;
      leds[i - 1] = CRGB::Black;
      leds[i - 2] = CRGB::Black;
      leds[27 - i] = CRGB::Black;
      leds[26 - i] = CRGB::Black;
      leds[25 - i] = color;
      FastLED.show();
    }
    if (sig2num() != 2) break;
    delay(60);
    for (int i = 12; i >= 3; i -= 3) {
      leds[i] = CRGB::Black;
      leds[i - 2] = CRGB::Black;
      leds[i - 1] = color;
      leds[27 - i] = CRGB::Black;
      leds[25 - i] = CRGB::Black;
      leds[26 - i] = color;
      FastLED.show();
    }
    if (sig2num() != 2) break;
    delay(100);
    for (int i = 12; i >= 3; i -= 3) {
      leds[i] = CRGB::Black;
      leds[i - 1] = CRGB::Black;
      leds[i - 2] = color;
      leds[27 - i] = color;
      leds[26 - i] = CRGB::Black;
      leds[25 - i] = CRGB::Black;
      FastLED.show();
    }
    if (sig2num() != 2) break;
    delay(140);
  }
}

void sea_car(CRGB color1, CRGB color2) {
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  fill_solid(leds, 7, color1);
  fill_solid(leds + 7, 6, color2);
  fill_solid(leds + 13, 7, color1);
  fill_solid(leds + 20, 6, color2);
  FastLED.show();
  if (sig2num() != 3) return;
  delay(60);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  if (sig2num() != 3) return;
  delay(60);

  fill_solid(leds, 7, color1);
  fill_solid(leds + 7, 6, color2);
  fill_solid(leds + 13, 7, color1);
  fill_solid(leds + 20, 6, color2);
  FastLED.show();
  if (sig2num() != 3) return;
  delay(60);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  if (sig2num() != 3) return;
  delay(60);

  fill_solid(leds, 7, color1);
  fill_solid(leds + 7, 6, color2);
  fill_solid(leds + 13, 7, color1);
  fill_solid(leds + 20, 6, color2);
  FastLED.show();
  if (sig2num() != 3) return;
  delay(60);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  if (sig2num() != 3) return;
  delay(300);
}

void sea_boat() {
  static CHSV sea_boat_hsv = CHSV(175, 255, 255);
  static int plus = -2;
  if (sea_boat_hsv.s >= 255) {
    plus = -2;
  }
  else if (sea_boat_hsv.s <= 200) {
    plus = 2;
  }
  sea_boat_hsv.s += plus;
  sea_boat_hsv.v += plus;
  fill_solid(leds, NUM_LEDS, sea_boat_hsv);
  FastLED.show();
  delay(80);
}

void wifi(CRGB color1, CRGB color2) {
  static int delay_time = 80;
  static int plus = 4;
  if (delay_time >= 100) {
    plus = -8;
  }
  else if (delay_time <= 20) {
    plus = 8;
  }
  delay_time += plus;
  for (int i = 0; i < 26; i += 4) {
    leds[i] = color1;
    leds[i + 1] = color1;
    leds[i + 2] = color2;
    leds[i + 3] = color2;
  }
  leds[24] = color1;
  leds[25] = color1;
  FastLED.show();
  delay(delay_time);
  for (int i = 2; i < 26; i += 4) {
    leds[i - 2] = color2;
    leds[i - 1] = color2;
    leds[i] = color1;
    leds[i + 1] = color1;
  }
  leds[24] = color2;
  leds[25] = color2;
  FastLED.show();
  delay(delay_time);
}

void quark() {
  static CHSV quark_hsv = CHSV(175, 255, 230);
  static int plus = -2;
  static int i = 0;
  if (quark_hsv.v >= 230) {
    plus = -2;
  }
  else if (quark_hsv.v <= 150) {
    plus = 2;
  }
  quark_hsv.v += plus;
  fill_solid(leds, NUM_LEDS, quark_hsv);
  leds[i] = CRGB::White;
  FastLED.show();
  delay(60);
  i += 1;
  if (i == 26) i = 0;
}

void earth() {
  static CHSV earth_hsv = CHSV(170, 255, 230);
  static int plus = -1;
  if (earth_hsv.h >= 170) {
    plus = -1;
  }
  else if (earth_hsv.h <= 120) {
    plus = 1;
  }
  earth_hsv.h += plus;
  fill_solid(leds, NUM_LEDS, earth_hsv);
  FastLED.show();
  delay(30);
}

void pay(CRGB color) {
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(35);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(120);

  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(35);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(80);
}

void cloud() {
  CHSV cloud_hsv1 = CHSV(170, 255, 230);
  CHSV cloud_hsv2 = CHSV(150, 100, 230);
  static int i = 0;
  fill_solid(leds, i, cloud_hsv2);
  fill_solid(leds + i, 7, cloud_hsv1);
  fill_solid(leds + i + 7, 6, cloud_hsv2);
  if (i >= 7)
    fill_solid(leds, i - 7 + 1, cloud_hsv1);
  else
    fill_solid(leds + i + 13, 7, cloud_hsv1);
  fill_solid(leds + i + 20, 6 - i, cloud_hsv2);
  FastLED.show();
  delay(20);
  i += 1;
  if (i == 13) i = 0;
}

void farm(CRGB ground) {
  static int i = 12;
  fill_solid(leds, NUM_LEDS, ground);
  leds[i - 1] = leds[i] = CRGB::Green;
  leds[26 - i] = leds[25 - i] = CRGB::Green;
  FastLED.show();
  delay(100);
  i -= 1;
  if (i == 0) i = 12;
}

