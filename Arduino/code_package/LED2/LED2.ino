#include <Arduino.h>
#define P0 8  // Arduino输出控制信号引脚
#define P1 9  // Arduino输出控制信号引脚
#define P2 10 // Arduino输出控制信号引脚
#define P3 11 // Arduino输出控制信号引脚

void setup()
{
  // put your setup code here, to run once:
  pinMode(P0, OUTPUT);
  pinMode(P1, OUTPUT);
  pinMode(P2, OUTPUT);
  pinMode(P3, OUTPUT);
  Serial1.begin(115200);
  num2sig(0);
}

void loop()
{
  static int i = 0;
  if (SerialRead() == 100) {
    num2sig(i);
    i += 1;
    delay(200);
  }
}

void num2sig(int num) {
  digitalWrite(P0, num % 2);
  digitalWrite(P1, num % 4 / 2);
  digitalWrite(P2, num % 8 / 4);
  digitalWrite(P3, num / 8);
}

int count = -1;   // 接收内容字节位置
int response = 0; // 接收内容

int SerialRead() // 读取WIFI接收内容
{
  count = -1;
  response = 0;
  delay(10); // 必须，防止硬件超负荷

  while (Serial1.available()) // 读取内容
    if (!transcoding((char)Serial1.read()))
      return -1;

  if (response) // 内容校验，response 不能为 0
    return response;
  else
    return -1;
}

bool transcoding(int g) // WIFI接收内容转码
{
  count++;
  // 把 g 最右边 byte 印成 Hex 俩位
  int a = g & 0xf0; // 左边 4 bits
  a = a >> 4;       // 右移 4 bits
  int b = g & 0x0f; // 右边 4 bits

  if (count == 6 || count == 7) // 数据位
    response = (response * 10 + a) * 10 + b;
  return true;
}

