#define LHP 14 // 左霍尔传感器引脚 Left Hall sensor Pin
#define MHP 15 // 中霍尔传感器引脚 Middle Hall sensor Pin
#define RHP 16 // 右霍尔传感器引脚 Right Hall sensor Pin

// #define LWP 3    // 左轮引脚 Left Wheel Pin
// #define RWP 2    // 右轮引脚 Right Wheel Pin
// #define LWI 1490 // 左轮初始值 Left Wheel Initial
// #define RWI 1490 // 右轮初始值 Right Wheel Initial

void setup()
{
  // 初始化霍尔传感器引脚
  pinMode(LHP, INPUT);
  pinMode(MHP, INPUT);
  pinMode(RHP, INPUT);

  // // 初始化伺服电机引脚
  // pinMode(LWP, OUTPUT);
  // pinMode(RWP, OUTPUT);
}

void loop()
{
  findPath(80); // 沿迹寻路
}

void findPath(int speed) // 沿迹寻路
{
  // 霍尔传感器 1 为无信号 0 为有信号
  int hallstate = digitalRead(LHP) * 4 + digitalRead(MHP) * 2 + digitalRead(RHP);
  switch (hallstate)
  {
  case 0:
  case 2:
  case 5:
  case 7:
    Wstraight(speed); // 直走代码
    break;
  case 1:          // LH 有 MH 有 RH 无
    Wturn(50, 80); // 左转1代码
    break;
  case 3:          // LH 有 MH 无 RH 无
    Wturn(20, 80); // 左转2代码
    break;
  case 4:          // LH 无 MH 有 RH 有
    Wturn(80, 50); // 右转1代码
    break;
  case 6:          // LH 无 MH 无 RH 有
    Wturn(80, 20); // 右转2代码
    break;
  }
}

// void WturnA(int angle) // 按角度转弯 顺时针为正 逆时针为负
// {
//   int time = 94.0 * (abs(angle) / 360.0); // 94.0 为转弯 360° 所需的计数
//   if (angle < 0)
//     for (int i = 0; i < time; i++)
//       Wturn(-80, 80);
//   else
//     for (int i = 0; i < time; i++)
//       Wturn(80, -80);
// }

// void Wturn(int Lspeed, int Rspeed) // 转弯
// {
//   LWrun(Lspeed);
//   RWrun(Rspeed);
//   delay(20); // 伺服电机周期 20ms
// }

// void Wstraight(int speed) // 直行
// {
//   RWrun(speed);
//   LWrun(speed);
//   delay(20); // 伺服电机周期 20ms
// }

// void LWrun(int speed) // 左轮运行
// {
//   digitalWrite(LWP, HIGH);
//   delayMicroseconds(LWI + speed);
//   digitalWrite(LWP, LOW);
// }

// void RWrun(int speed) // 右轮运行
// {
//   digitalWrite(RWP, HIGH);
//   delayMicroseconds(RWI - speed);
//   digitalWrite(RWP, LOW);
// }
