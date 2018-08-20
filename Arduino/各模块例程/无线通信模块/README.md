# 无线通信模块

注意：无线通信模块工作电压为 **3.3V**，使用 **5V** 电压极易导致烧卡

## 接线方式

 Arduino 引脚 | RFID 模块引脚
-------------|-------------
 0           | TX
 1           | RX
 VCC         | VCC
 GND         | GND

说明：

1. 无线模块上的 `VCC` 和 `GND` 分别只需和 Arduino 连接一根就行，无需全部连接

2. 请使用 **硬串口**，并设置波特率为 `115200`。如需修改此项值，请参考 [食用方法 step 4](#step-4)

## 食用方法

由于本次使用的无线通信模块为 DL-LN3x 系列，使用的是商家自定义的协议，**不支持 zigbee 协议**，同时官方并没有给出 Arduino 的例程或者库函数，整个使用过程中体验极差

### step 1

故，食用的第一步是弄清无线模块的通信机制：

由于此模块属于自动组网。模块通电后，位于同一网络 ID 下的模块将自动组网，这点还是值得表扬的

*（至于如何对模块的网络 ID 进行修改，将在下文中 [step 4](#step-4) 中提及）*

在模块间组网后，就需要进行相互间收发包通信

PS：在进行以下步骤前先阅读一遍 [官方手册（说明书）](./DL-LN3X说明书2.0.pdf) 和 [快速使用手册](./DL-LN系列无线自组网模块快速使用手册.pdf)

### step 2

由于没有相关库，整个包的封装都需要自己来实现：

关于包结构的定义，请参见 [官方手册 第 2 节 - Uart 通信协议](./DL-LN3X说明书2.0.pdf#[{"num":38,"gen":0},{"name":"XYZ"},40,720,0])

了解协议后，我们就可以开始写自己的打包和解包函数了

### step 3

为了减少工作量，将所有包的数据位都设在 0-9 范围内，A-F 不管了

```c
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
```

### step 4

模块的其他硬件配置请参见 [官方手册 3.3.2 节 - 设置信息](./DL-LN3X说明书2.0.pdf#[{"num":108,"gen":0},{"name":"XYZ"},40,663,0])

## 例程食用说明

例程目录为 `./WIFI`，直接打开 [`./WIFI/WIFI.ino`](./Servo360/Servo360.ino) 并烧入

可以使用 USB-TTL 模块再接一个无线模块，打开串口调试工具，看看会收到什么

此处 [串口调试工具](./UartAssist.exe) 推荐使用我提供的这个版本，其他版本存在收到数据部分显示不同情况，原因未知