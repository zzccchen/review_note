#include "FastLED.h"            // 此示例程序需要使用FastLED库

#define NUM_LEDS_T 115             // LED灯珠数量
#define NUM_LEDS_L 109             // LED灯珠数量
#define NUM_LEDS_S 26              // LED灯珠数量

#define LED_S0 2                // Arduino输出控制信号引脚
#define LED_S1 3                // Arduino输出控制信号引脚
#define LED_S2 4                // Arduino输出控制信号引脚

#define LED_L0 5                // Arduino输出控制信号引脚
#define LED_T0 6                // Arduino输出控制信号引脚

#define LED_L1 7                // Arduino输出控制信号引脚
#define LED_L2 8                // Arduino输出控制信号引脚
#define LED_L3 9                // Arduino输出控制信号引脚

#define LED_T1 10                // Arduino输出控制信号引脚
#define LED_L4 11                // Arduino输出控制信号引脚

#define LED_S3 12                // Arduino输出控制信号引脚
#define LED_S4 13                // Arduino输出控制信号引脚
#define LED_S5 35                // Arduino输出控制信号引脚

#define P0 30
#define P1 31
#define P2 32
#define P3 33

#define START 151 // 启动代码

#define LED_TYPE WS2812         // LED灯带型号
#define COLOR_ORDER GRB         // RGB灯珠中红色、绿色、蓝色LED的排列顺序
uint8_t max_bright = 255;       // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高

CRGB leds_t0[NUM_LEDS_T];            // 建立光带leds_t0
CRGB leds_t1[NUM_LEDS_T];            // 建立光带leds_t1

CRGB leds_l0[NUM_LEDS_L];            // 建立光带leds_l0
CRGB leds_l1[NUM_LEDS_L];            // 建立光带leds_l1
CRGB leds_l2[NUM_LEDS_L];            // 建立光带leds_l2
CRGB leds_l3[NUM_LEDS_L];            // 建立光带leds_l3
CRGB leds_l4[NUM_LEDS_L];            // 建立光带leds_l4

CRGB leds_s0[NUM_LEDS_S];            // 建立光带leds_s0
CRGB leds_s1[NUM_LEDS_S];            // 建立光带leds_s1
CRGB leds_s2[NUM_LEDS_S];            // 建立光带leds_s2
CRGB leds_s3[NUM_LEDS_S];            // 建立光带leds_s3
CRGB leds_s4[NUM_LEDS_S];            // 建立光带leds_s4
CRGB leds_s5[NUM_LEDS_S];            // 建立光带leds_s5

int beginHue = 0;
int endHue = 300;
uint8_t deltaHue = 28;

void setup() {
  pinMode(P0, INPUT);
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(P3, INPUT);

  LEDS.addLeds<LED_TYPE, LED_T0, COLOR_ORDER>(leds_t0, NUM_LEDS_T);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_T1, COLOR_ORDER>(leds_t1, NUM_LEDS_T);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_L0, COLOR_ORDER>(leds_l0, NUM_LEDS_L);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_L1, COLOR_ORDER>(leds_l1, NUM_LEDS_L);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_L2, COLOR_ORDER>(leds_l2, NUM_LEDS_L);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_L3, COLOR_ORDER>(leds_l3, NUM_LEDS_L);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_L4, COLOR_ORDER>(leds_l4, NUM_LEDS_L);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_S0, COLOR_ORDER>(leds_s0, NUM_LEDS_S);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_S1, COLOR_ORDER>(leds_s1, NUM_LEDS_S);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_S2, COLOR_ORDER>(leds_s2, NUM_LEDS_S);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_S3, COLOR_ORDER>(leds_s3, NUM_LEDS_S);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_S4, COLOR_ORDER>(leds_s4, NUM_LEDS_S);  // 初始化光带
  LEDS.addLeds<LED_TYPE, LED_S5, COLOR_ORDER>(leds_s5, NUM_LEDS_S);  // 初始化光带
  FastLED.setBrightness(max_bright);                                // 设置光带亮度

  // 硬串口初始化
  Serial.begin(115200);
}

CRGB hp = CRGB(253, 175, 17);

void loop() {
  static int i = 0;
  if (i != sig2num() % 10) {
    i = sig2num() % 10;
    fill_dark_noshow();
  }
  switch (sig2num() % 10) {
    case 1: case 2:
      sea();
      break;
    case 3:
      wifi();
      break;
    case 6:
      quark();
      break;
    case 9:
      cloud();
      break;
    default:
      fill_dark();
      break;
  }
}

int sig2num() {
  return digitalRead(P0) + 2 * digitalRead(P1) + 4 * digitalRead(P2) + 8 * digitalRead(P3);
}

void fill_dark_noshow() {
  fill_solid(leds_l0, NUM_LEDS_L, CRGB::Black);
  fill_solid(leds_l1, NUM_LEDS_L, CRGB::Black);
  fill_solid(leds_l2, NUM_LEDS_L, CRGB::Black);
  fill_solid(leds_l3, NUM_LEDS_L, CRGB::Black);
  fill_solid(leds_l4, NUM_LEDS_L, CRGB::Black);
  fill_solid(leds_s0, NUM_LEDS_S, CRGB::Black);
  fill_solid(leds_s1, NUM_LEDS_S, CRGB::Black);
  fill_solid(leds_s2, NUM_LEDS_S, CRGB::Black);
  fill_solid(leds_s3, NUM_LEDS_S, CRGB::Black);
  fill_solid(leds_s4, NUM_LEDS_S, CRGB::Black);
  fill_solid(leds_s5, NUM_LEDS_S, CRGB::Black);
  fill_solid(leds_t0, NUM_LEDS_T, CRGB::Black);
  fill_solid(leds_t1, NUM_LEDS_T, CRGB::Black);
}

void fill_dark() {
  fill_dark_noshow();
  FastLED.show();
}

void sea() {
  static int startnum = 0;
  startnum += 2;
  fill_palette(leds_l0, NUM_LEDS_L, startnum, 6, OceanColors_p, 255, LINEARBLEND);
  fill_palette(leds_l1, NUM_LEDS_L, startnum + 60, 6, OceanColors_p, 255, LINEARBLEND);
  fill_palette(leds_l2, NUM_LEDS_L, startnum + 120, 6, OceanColors_p, 255, LINEARBLEND);
  fill_palette(leds_l3, NUM_LEDS_L, startnum + 180, 6, OceanColors_p, 255, LINEARBLEND);
  fill_palette(leds_l4, NUM_LEDS_L, startnum + 240, 6, OceanColors_p, 255, LINEARBLEND);
  for (int i = 28; i < 82 ; i += 2)
  {
    leds_l0[i] = CRGB::White;
    leds_l1[i] = CRGB::White;
    leds_l3[i] = CRGB::White;
    leds_l4[i] = CRGB::White;
  }
  for (int i = 0; i < 26 ; i += 2)
  {
    leds_s0[i] = CRGB::White;
    leds_s1[i] = CRGB::White;
    leds_s2[i] = CRGB::White;
    leds_s3[i] = CRGB::White;
    leds_s4[i] = CRGB::White;
    leds_s5[i] = CRGB::White;
  }
  FastLED.show();
  delay(3);
}

void wifi() {
  static int startnum = 0;
  startnum += 18;
  fill_palette(leds_t0, NUM_LEDS_T, startnum, 20, OceanColors_p, 255, LINEARBLEND);
  fill_palette(leds_t1, NUM_LEDS_T, startnum + 60, 20, OceanColors_p, 255, LINEARBLEND);
  FastLED.show();
  delay(30);
  startnum += 3;
  fill_palette(leds_t0, NUM_LEDS_T, startnum, 20, OceanColors_p, 255, LINEARBLEND);
  fill_palette(leds_t1, NUM_LEDS_T, startnum + 60, 20, OceanColors_p, 255, LINEARBLEND);
  for (int i = 1; i < NUM_LEDS_T ; i += 2)
  {
    leds_t0[i] = CRGB::White;
    leds_t1[i] = CRGB::White;
  }
  FastLED.show();
  delay(5);
}

void quark() {
  static int num = 0;
  fill_palette(leds_s0, NUM_LEDS_S, num, 30, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_s2, NUM_LEDS_S, num, 30, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_s3, NUM_LEDS_S, num, 30, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_s5, NUM_LEDS_S, num, 30, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l1, NUM_LEDS_S + 1, num, 30, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l1 + NUM_LEDS_L - NUM_LEDS_S - 2, NUM_LEDS_S + 1, num, 30, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l3, NUM_LEDS_S + 1, num, 30, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l3 + NUM_LEDS_L - NUM_LEDS_S - 2, NUM_LEDS_S + 1, num, 30, CloudColors_p, 255, LINEARBLEND);
  FastLED.show();
  delay(3);
  num += 15;
}

void cloud() {
  static int num = 0;
  static int i = 12;
  static int plus = 1;
  fill_palette(leds_l0, NUM_LEDS_L, num, 6, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l1, NUM_LEDS_L, num + 60, 6, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l2, NUM_LEDS_L, num + 120, 6, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l3, NUM_LEDS_L, num + 180, 6, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l4, NUM_LEDS_L, num + 240, 6, CloudColors_p, 255, LINEARBLEND);
  FastLED.show();
  delay(5);
  num += i;
  i += plus;
  if (i == 85)
    plus = -plus;
  else if (i == 12)
    plus = -plus;
}

void farm() {
  fill_palette(leds_l0, NUM_LEDS_L, 0, 6, LavaColors_p, 255, LINEARBLEND);
  fill_palette(leds_l1, NUM_LEDS_L, 60, 6, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l2, NUM_LEDS_L, 120, 6, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l3, NUM_LEDS_L, 180, 6, CloudColors_p, 255, LINEARBLEND);
  fill_palette(leds_l4, NUM_LEDS_L, 240, 6, CloudColors_p, 255, LINEARBLEND);
}

