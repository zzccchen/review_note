#include <SPI.h>
#include <RFID.h>

RFID rfid(10,5); // 引脚接法见README
void setup()
{
  Serial.begin(9600);
  SPI.begin(); // 串行外设初始化
  rfid.init(); // 读卡器初始化
}

void loop()
{
  // 找到卡
  if (rfid.isCard()) {
    Serial.println("Find the card!"); 
    if (rfid.readCardSerial()) 
    {
      // 打印卡内容
      Serial.print("The card's content is : ");
      Serial.print(rfid.serNum[0],HEX);
      Serial.print(rfid.serNum[1],HEX);
      Serial.print(rfid.serNum[2],HEX);
      Serial.print(rfid.serNum[3],HEX);
      Serial.print(rfid.serNum[4],HEX);
      Serial.print(rfid.serNum[5],HEX);
      Serial.print(rfid.serNum[6],HEX);
      Serial.print(rfid.serNum[7],HEX);
      Serial.print(rfid.serNum[8],HEX);
      Serial.print(rfid.serNum[9],HEX);

      // 打印卡序列号
      Serial.print("The card's number is : ");
      Serial.print(*rfid.serNum);
      Serial.println(" ");
    }
    // 选卡，可返回卡容量（锁定卡片，防止多数读取），去掉本行将连续读卡
    rfid.selectTag(rfid.serNum);
  }
  // 使卡休眠 在实际使用中较少用到
  rfid.halt();
}
