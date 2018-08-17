# Arduino

参加教育机器人大赛弄的 `Arduino`，把用到的坑和相关库用法记下吧

## 平台说明

硬件 | 名称
-----|-------
开发板 | Arduino UNO R3
拓展板 | Arduino sensor sheld V5 改

![拓展板功能图](./image/Arduino-Sensor-Shield-v5.0-Functional-Diagram.jpg)

## 点亮你的流水灯

```c
// 给2号引脚连接的设备设置一个别名 PIN_LED1
#define PIN_LED1 2
#define PIN_LED2 3 // 同上
#define PIN_LED3 4 // 同上

// 在板子启动或者复位重启后，setup部分的程序只会运行一次
void setup()
{
  // 将LED引脚设置为输出状态
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
}

// setup部分程序运行完后，loop部分的程序会不断重复运行
void loop()
{
  // 亮 灭 灭
  digitalWrite(PIN_LED1, HIGH); // 点亮 LED1
  digitalWrite(PIN_LED2, LOW);  // 熄灭 LED2
  digitalWrite(PIN_LED3, LOW);  // 熄灭 LED3
  delay(500);                   // 持续 500ms

  // 灭 亮 灭
  digitalWrite(PIN_LED1, LOW);  // 熄灭 LED1
  digitalWrite(PIN_LED2, HIGH); // 点亮 LED2
  digitalWrite(PIN_LED3, LOW);  // 熄灭 LED3
  delay(500);                   // 持续 500ms

  // 灭 灭 亮
  digitalWrite(PIN_LED1, LOW);  // 熄灭 LED1
  digitalWrite(PIN_LED2, LOW);  // 熄灭 LED2
  digitalWrite(PIN_LED3, HIGH); // 点亮 LED3
  delay(500);                   // 持续 500ms
}
```

说明：

1. Arduino 板子的 1、2 引脚默认分别为硬串口的 `RX` 和 `TX` 引脚，自带 5v 电压

   如果外设中使用到硬串口，则会使用到该引脚

   烧录中可能会遇到无法烧入的问题，目前方案是拔掉接线后烧入

2. 引脚可设置为三种模式：

   `INPUT` 输入模式、`OUTPUT` 输出模式、`INPUT_PULLUP` 输入上拉模式

   设置方法为：```pinMode(pin, mode);```

   参数 `pin` 为指定配置的引脚编号，参数 `mode` 为指定的配置模式

3. 可以通过 ```digitalWrite(pin, value);``` 让引脚输出高电平或者是低电平

   此时对应的引脚需配置为输出模式

   Arduino 中输出的低电平（`LOW`）为 0V，输出的高电平（`HIGH`）为当前 Arduino 的工作电压（在 UNO R3 上为 5v）

4. 可以用 ```int value = digitalRead(pin);``` 读取引脚外部输入的数字信号

   返回值 value 为获取到的信号状态，1 为高电平，0 为低电平

   Arduino UNO 会将大于 3V 的输入电压视为高电平识别，小于 1.5V 的电压视为低电平识别

相关教程：

[数字 I/O 的使用](https://www.arduino.cn/thread-74476-1-1.html)

## 串口通讯 - Hello World

### 硬串口

```c
void setup()
{
  Serial.begin(115200); // 硬串口初始化
}

// setup部分程序运行完后，loop部分的程序会不断重复运行
void loop()
{
  Serial.println("Hello World"); // 打印 “Hello World”
  delay(1000); // 避免打印速度过快
}
```

说明：

1. 烧入代码，连上 USB 线，打开 IDE 的 `工具 - 串口监视器`，设置正确的波特率，例程中为 `115200`

   观察串口监视器打印的内容：以每秒一次的频率打印 “Hello World”

2. 串口通信中有 `print()` 和 `write()` 两种输出方式

   两者比较如下：

   当使用 `print()` 发送一个数据时，Arduino 发送的并不是数据本身，而是将数据转换成字符，再将对应的 ASCII 码发送出去，串口监视器接收到 ASCII 码，则会将其转换并显示对应的字符。因此，使用 `print()` 函数是以 ASCII 码的形式输出数据到串口

   而当使用 `write()` 函数时，Arduino 发送的是数值本身。但是串口监视器接收到数据后，会将数值当做 ASCII 码而显示其对应的字符

3. 上文代码中的 `println()` 效果为 `print()` 后并添加换行

更多用法请参考相关教程，部分必须用法在后文也会提及：

[print() 和 write() 输出方式的差异](https://www.cnblogs.com/fqhy/p/7966169.html)

[Arduino - 串口操作函数与示例代码大全（推荐阅读）](https://blog.csdn.net/iracer/article/details/50334041)

### 软串口

软串口在实际使用中不推荐使用，详细原因在 [遇到的坑](./遇到的坑.md#3) 中提及

更多用法请参考相关教程：

[软件模拟串口通信 —— SoftwareSerial 库的使用](https://www.arduino.cn/thread-47262-1-1.html)

## 进阶教程

建议食用顺序：`本README` -> [`各模块例程/IC卡`](./各模块例程/IC卡/README.md)
