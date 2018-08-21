#define START 151 // 启动代码

unsigned char sendCmd0[11] = {0xfe, 0x06, 0x93, 0x93, 0xfe, 0xfd, 0xfe, 0xfd, 0x01, 0x00, 0xff}; // 主机发

void setup()
{
  Serial.begin(115200); // 硬串口初始化

  // start() // 一键启动
}

void loop()
{
  SerialWrite(sendCmd0);
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

void Dready() // 主机信号接收（特殊用）
{
  SerialRead(); // 清除缓冲区
  while (SerialRead() != 100){};
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
  delay(2); // 必须，防止硬件超负荷

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