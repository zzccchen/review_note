# 360° 舵机

`舵机` 包括 `360°` 舵机和 `180°` 舵机，而舵机亦是伺服舵机的一种

`360°` 舵机与 `180°` 舵机的区别是：给 `180°` 舵机一个 `PWM` 信号，舵机会转到一个特定角度；而给 `360°` 舵机一个 `PWM` 信号，舵机会以一个特定的速度转动，类似与电机。但与电机不同的是，`360°` 舵机是闭环控制，速度控制稳定

为了区分 `360°` 舵机和 `180°` 舵机，以下部分地方将 `360°` 舵机简称为“伺服电机”，而 `180°` 舵机简称为“舵机”

## 接线方式

将 `VCC`、`GND`、`SIG` 引脚一一对应即可

## 食用方法

`360°` 舵机操作无需使用相关库函数，其转动由 `PWM` 脉冲控制，`PWM` 脉冲周期为 20ms

高电平宽度为约 1500μs 时，伺服电机速度约为 0；当宽度为小于 1500μs 时，伺服电机正转；当宽度为大于 1500μs 时，伺服电机反转

正转和反转速度视不同舵机而定。而由于舵机在不同脉冲宽度下的速度变化是非线性的，因此在不同速度下需要对左右轮舵机进行矫零，如：

```c
#define LWP 3    // 左轮引脚 Left Wheel Pin
#define RWP 2    // 右轮引脚 Right Wheel Pin
#define LWI 1500 // 左轮初始值 Left Wheel Initial
#define RWI 1500 // 右轮初始值 Right Wheel Initial

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
```

## 例程食用说明

例程目录为 `./Servo360`，直接打开 [`./Servo360/Servo360.ino`](./Servo360/Servo360.ino) 并烧入

小车会直行一段路后顺时针掉头，并循环此过程

例程中包含封装好的小车移动函数，可直接使用

注意：

1. 在使用 `WturnA(angle)` 函数中，参数 `angle`（角度值）应小于绝对值 360°

   一方面可以避免内部值超出 `int` 类型范围，一方面方便阅读调试，如：

   ```c
   // 不推荐写法     // 不推荐写法
   WturnA(720);     WturnA(540);

   // 推荐写法      // 推荐写法
   WturnA(360);     WturnA(360);
   WturnA(360);     WturnA(180);
   ```

