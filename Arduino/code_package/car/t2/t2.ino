#include <Arduino.h>
#include <SPI.h>            // IC卡头文件
#include <RFID.h>           // IC卡头文件

#define LHP 14 // 左霍尔传感器引脚 Left Hall sensor Pin
#define MHP 15 // 中霍尔传感器引脚 Middle Hall sensor Pin
#define RHP 16 // 右霍尔传感器引脚 Right Hall sensor Pin

#define LWP 3    // 左轮引脚 Left Wheel Pin
#define MWP 4    // 中轮引脚 Middle Wheel Pin
#define RWP 2    // 右轮引脚 Right Wheel Pin
#define LWI 1483 // 左轮初始值 Left Wheel Initial
#define MWI 1500 // 中轮初始值 Middle Wheel Initial
#define RWI 1460 // 右轮初始值 Right Wheel Initial

#define P0 6 // LED通信引脚
#define P1 7 // LED通信引脚
#define P2 8 // LED通信引脚
#define P3 9 // LED通信引脚

#define REDP A5 // 红外引脚

#define START 151 // 启动代码

RFID rfid(10, 5); // 读卡器初始化

unsigned char sendCmd0[11] = {0xfe, 0x06, 0x93, 0x93, 0xfe, 0xfd, 0xfe, 0xfd, 0x01, 0x00, 0xff}; // 主机发

unsigned char sendCmd1[11] = {0xfe, 0x06, 0x93, 0x93, 0x25, 0x4d, 0x01, 0x01, 0xff}; // 从机1发
unsigned char sendCmd2[11] = {0xfe, 0x06, 0x93, 0x93, 0x25, 0x4d, 0x01, 0x02, 0xff}; // 从机2发
unsigned char sendCmd3[11] = {0xfe, 0x06, 0x93, 0x93, 0x25, 0x4d, 0x01, 0x03, 0xff}; // 从机3发
unsigned char sendCmd4[11] = {0xfe, 0x06, 0x93, 0x93, 0x25, 0x4d, 0x01, 0x04, 0xff}; // 从机4发

void setup()
{
  // 初始化LED通信引脚
  pinMode(P0, OUTPUT);
  pinMode(P1, OUTPUT);
  pinMode(P2, OUTPUT);
  pinMode(P3, OUTPUT);
  num2sig(0);

  // 初始化伺服电机引脚
  pinMode(LWP, OUTPUT);
  pinMode(MWP, OUTPUT);
  pinMode(RWP, OUTPUT);

  // 初始化霍尔传感器引脚
  pinMode(LHP, INPUT);
  pinMode(MHP, INPUT);
  pinMode(RHP, INPUT);

  // 初始化红外传感器引脚
  pinMode(REDP, INPUT);

  // 读卡器初始化
  SPI.begin();
  rfid.init();

  // 硬串口初始化
  Serial.begin(115200);

  // 一键启动
  start();
  num2sig(1);
  delay(10);
  num2sig(2);
  delay(4230);
}

int cardno[] = {237, 212, 29, 77, 84, 173, 52, 61, 0}; // 卡号数组
void loop()
{
  static int step = 0;
  while (!findCard(cardno[step]))
  {
    switch (step) // 未就位动作
    {
      case 7:
        findPath(60);
        break;
      case 8:
        break;
      default:
        findPath(90);
        break;
    }
  }
  for (int i = 0; i < 10; i++) // 前进补偿
    findPath(50);

  switch (step) // 就位动作
  {
    case 0: case 5:
      WturnA(-90);
      break;
    case 1: case 2: case 4:
      WturnA(90);
      break;
    case 3:
      Cready(sendCmd2);
      num2sig(4);
      WturnM();
      WturnA(65);
      break;
    case 6:
      WturnA(180);
      Cready(sendCmd2);
      delay(100);
      Sready(2);
      delay(7000);
      Sready(2);
      break;
    case 7:
      delay(5000);
      Cready(sendCmd2);
      num2sig(5);
      WturnM();
      WturnA(45);
      WturnA(360);
      WturnA(360);
      Dready();
      delay(200);
      Dready();
      delay(200);
      Dready();
      num2sig(9);
      WturnM();
      WturnA(360);   
      Dready();
      delay(200);
      Dready();
      num2sig(10);
      WturnM();
      WturnA(360);
      Dready();
      num2sig(9);
      WturnM();
      WturnA(360);
      break;
  }
  step++;
}

void num2sig(int num) {
  digitalWrite(P0, num % 2);
  digitalWrite(P1, num % 4 / 2);
  digitalWrite(P2, num % 8 / 4);
  digitalWrite(P3, num / 8);
}

void start() // 一键启动
{
  SerialRead(); // 清除缓冲区
  while (true)
    if (SerialRead() == START)
      break;
}

void Sready(int nums) // 主机就位信号发送
{
  int status1 = 0; // 从机1号状态
  int status2 = 0; // 从机2号状态
  int status3 = 0; // 从机3号状态
  int status4 = 0; // 从机4号状态

  SerialRead(); // 清除缓冲区
  while ((status1 + status2 + status3 + status4) < nums)
  {
    switch (SerialRead())
    {
      case 101:
        status1 = 1;
        break;
      case 102:
        status2 = 1;
        break;
      case 103:
        status3 = 1;
        break;
      case 104:
        status4 = 1;
        break;
    }
  }
  for (int i = 0; i < 10; i++)
    SerialWrite(sendCmd0);
  delay(100);
}

void Dready() // 主机信号接收（特殊用）
{
  SerialRead(); // 清除缓冲区
  while (SerialRead() != 100) {};
}

void Cready(unsigned char *content) // 从机就位信号发送
{
  SerialRead(); // 清除缓冲区
  while (true)
  {
    SerialWrite(content); // 就位信号发送
    if (SerialRead() == 100)
      break;
  }
}

void SerialWrite(unsigned char *content) // WIFI发送内容
{
  delay(10); // 必须，防止硬件超负荷
  Serial.write(content, 16); // 16 进制发送
}

int count = -1;   // 接收内容字节位置
int response = 0; // 接收内容

int SerialRead() // 读取WIFI接收内容
{
  count = -1;
  response = 0;
  delay(10); // 必须，防止硬件超负荷

  while (Serial.available()) // 读取内容
    if (!transcoding((char)Serial.read()))
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

bool findCard(int cardno) // 找卡
{
  if (rfid.isCard()) // 读取卡序列号
    if (rfid.readCardSerial() && *rfid.serNum == cardno)
      return true;
  return false;
}

void findPathR(int speed) // 向后寻路
{
  // 霍尔传感器 1 为无信号 0 为有信号
  int hallstate = digitalRead(LHP) * 4 + digitalRead(MHP) * 2 + digitalRead(RHP);
  switch (hallstate)
  {
    case 0: case 2: case 5: case 7:
      Wstraight(speed);
      break;
    case 1: // LH 有 MH 有 RH 无
      Wturn(-80, -50);
      break;
    case 3: // LH 有 MH 无 RH 无
      Wturn(-80, -20);
      break;
    case 4: // LH 无 MH 有 RH 有
      Wturn(-50, -80);
      break;
    case 6: // LH 无 MH 无 RH 有
      Wturn(-20, -80);
      break;
  }
}

void findPath(int speed) // 寻路
{
  // 霍尔传感器 1 为无信号 0 为有信号
  int hallstate = digitalRead(LHP) * 4 + digitalRead(MHP) * 2 + digitalRead(RHP);
  switch (hallstate)
  {
    case 0: case 2: case 5: case 7:
      Wstraight(speed);
      break;
    case 1: // LH 有 MH 有 RH 无
      Wturn(50, 80);
      break;
    case 3: // LH 有 MH 无 RH 无
      Wturn(20, 80);
      break;
    case 4: // LH 无 MH 有 RH 有
      Wturn(80, 50);
      break;
    case 6: // LH 无 MH 无 RH 有
      Wturn(80, 20);
      break;
  }
}

void WturnM() // 顺时针旋转270°并转卷轴
{
  int time = 95 * (315 / 360.0);
  int MWrunSpeed = 285;
  int i = 0, count = 0;
  for (i = 0; i < 20; i++) {
    LWrun(80);
    RWrun(-80);
    MWrun(MWrunSpeed);
    delay(20); // 伺服电机周期 20ms
  }
  for (i; i < time; i++) {
    LWrun(80);
    RWrun(-80);
    MWrun(MWrunSpeed);
    delay(20); // 伺服电机周期 20ms
    if (digitalRead(REDP) == 1) { // 黑 1 白 0
      if (count == 2)
        break;
      else
        count += 1;
    }
  }
  for (i; i < time; i++) {
    LWrun(80);
    RWrun(-80);
    delay(20); // 伺服电机周期 20ms
  }
}

void WturnA(int angle) // 按角度转弯 最大角度360
{
  int time = 98 * (abs(angle) / 360.0); // 93.5 为转弯 360°所需的计数
  if (angle < 0)
    for (int i = 0; i < time; i++)
      Wturn(-80, 80);
  else
    for (int i = 0; i < time; i++)
      Wturn(80, -80);
}

void Wturn(int Lspeed, int Rspeed) // 转弯
{
  LWrun(Lspeed);
  RWrun(Rspeed);
  delay(20); // 伺服电机周期 20ms
}

void Wstraight(int speed) // 直行
{
  RWrun(speed);
  LWrun(speed);
  delay(20); // 伺服电机周期 20ms
}

void MWrun(int speed) // 中轮运行
{
  digitalWrite(MWP, HIGH);
  delayMicroseconds(MWI + speed);
  digitalWrite(MWP, LOW);
}

void LWrun(int speed) // 左轮运行
{
  digitalWrite(LWP, HIGH);
  delayMicroseconds(LWI + speed);
  digitalWrite(LWP, LOW);
}

void RWrun(int speed) // 右轮运行
{
  digitalWrite(RWP, HIGH);
  delayMicroseconds(RWI - speed);
  digitalWrite(RWP, LOW);
}
