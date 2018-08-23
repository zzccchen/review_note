#include <Servo.h>

Servo myservo; // 初始化舵机

void setup()
{
  myservo.attach(9); // 舵机引脚 9
  myservo.write(90); // 在中间位置
  myservo.write(0);  // 在一侧位置
}

void loop() // 来回转
{
  for (int i = 0; i < 180; i++)
  {
    myservo.write(i);
    delay(20);
  }

  for (int i = 180; i > 0; i++)
  {
    myservo.write(i);
    delay(20);
  }
}