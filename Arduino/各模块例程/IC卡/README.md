# IC 卡

注意：IC 卡模块工作电压为 **3.3V**，使用 **5V** 电压极易导致烧卡

## 接线方式

 Arduino 引脚 | RFID 模块引脚
-------------|-------------
 D5          | RST
 D10         | SDA
 D11         | MOSI
 D12         | MISO
 D13         | SCK

说明：*以上的 D5 引脚即为 5 号引脚，其他同理*

## 第三方库 - RFID

IC 卡模块采用 RC522 芯片，在代码中使用了第三方库 - `RFID` 库

其安装方式如下：

> 将 `./RFID` 文件夹拷贝到 `C:\Users\你的用户名\Documents\Arduino\libraries` 目录下
>
> 最终效果为 `C:\Users\你的用户名\Documents\Arduino\libraries\RFID`，并重启你的 IDE

注意：

1. 需要拷贝整个文件夹，而不只是文件夹下的 `RFID.cpp` 和 `RFID.h` 两个文件

2. 只方法仅对 Arduino 自带的 IDE 有效

3. 安装头文件不只有以上一种方式，其他方法请自行百度

## 例程食用说明

例程目录为 `./IC`，直接打开 [`./IC/IC.ino`](./IC/IC.ino) 并烧入

保持 USB 连接，并打开 IDE 的 `工具 - 串口监视器`，设置正确的波特率，例程中为 `9600`

观察每次刷卡时，串口监视器打印的内容
