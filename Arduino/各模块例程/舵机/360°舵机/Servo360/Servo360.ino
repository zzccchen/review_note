#define LWP 3    // 左轮引脚 Left Wheel Pin
#define RWP 2    // 右轮引脚 Right Wheel Pin
#define LWI 1500 // 左轮初始值 Left Wheel Initial
#define RWI 1500 // 右轮初始值 Right Wheel Initial

void setup()
{
  // 初始化伺服电机引脚
  pinMode(LWP, OUTPUT);
  pinMode(RWP, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 200; i++) // 直行一段路
    Wstraight(80);

  delay(1000);
  Wstraight(180); // 顺时针掉头
}

void WturnA(int angle) // 按角度转弯 顺时针为正 逆时针为负
{
  int time = 94.0 * (abs(angle) / 360.0); // 94.0 为转弯 360° 所需的计数
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
