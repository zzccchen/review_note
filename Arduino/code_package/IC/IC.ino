#include <SPI.h>
#include <RFID.h>

RFID rfid(10,5);   //D10--读卡器MOSI引脚、D5--读卡器RST引脚
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop()
{
  //找卡
  if (rfid.isCard()) {
    Serial.println("Find the card!");
    //读取卡序列号
    if (rfid.readCardSerial()) {
      Serial.print("The card's number is  : ");
      // Serial.print(rfid.serNum[0],HEX);
      // Serial.print(rfid.serNum[1],HEX);
      // Serial.print(rfid.serNum[2],HEX);
      // Serial.print(rfid.serNum[3],HEX);
      // Serial.print(rfid.serNum[4],HEX);
      // Serial.print(rfid.serNum[5],HEX);
      // Serial.print(rfid.serNum[6],HEX);
      // Serial.print(rfid.serNum[7],HEX);
      // Serial.print(rfid.serNum[8],HEX);
      // Serial.print(rfid.serNum[9],HEX);
      // Serial.print(rfid.serNum[10],HEX);
      // Serial.print(rfid.serNum[11],HEX);
      // Serial.print(rfid.serNum[12],HEX);
      // Serial.print(rfid.serNum[13],HEX);
      // Serial.print(rfid.serNum[14],HEX);
      // Serial.print(rfid.serNum[15],HEX);
      // Serial.print(rfid.serNum[16],HEX);
      // Serial.print(rfid.serNum[17],HEX);
      // Serial.print(rfid.serNum[18],HEX);
      // Serial.print(rfid.serNum[19],HEX);
      // Serial.print(rfid.serNum[20],HEX);
      // Serial.print(rfid.serNum[21],HEX);
      // Serial.print(rfid.serNum[22],HEX);
      // Serial.print(rfid.serNum[23],HEX);
      // Serial.print(rfid.serNum[24],HEX);
      // Serial.print(rfid.serNum[25],HEX);
      // Serial.print(rfid.serNum[26],HEX);
      // Serial.print(rfid.serNum[27],HEX);
      // Serial.print(rfid.serNum[28],HEX);
      // Serial.print(rfid.serNum[29],HEX);
      Serial.println(" ");
      Serial.print(*rfid.serNum);
      Serial.println(" ");
    }
    //选卡，可返回卡容量（锁定卡片，防止多数读取），去掉本行将连续读卡
    rfid.selectTag(rfid.serNum);
  }
  
  rfid.halt();
}
