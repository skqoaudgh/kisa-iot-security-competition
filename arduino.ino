#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(A1, DHT11);

int pos = 11; // "Received: " 의 글자 수가 공백 포함 10

void setup() {
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.println("Waiting data..");
    // lcd의 불을 키고 메시지 출력
}

void loop() {
    // 데이터를 보낸 후에는 1초 대기. 데이터를 받고 나서는 바로 다음 loop 실행
    if(Serial.available()) { // 서버에서 데이터를 받음
        int incomingByte = Serial.read();
        if(pos == 11) { // 새로운 데이터가 들어오면 lcd를 초기화
            lcd.clear();
            lcd.print("Received: ");
        }
        lcd.setCursor(pos++, 0);
        lcd.print(String(incomingByte));
    }
    else {
        int t = dht.readTemperature();
        Serial.println(t); // 온도 데이터를 서버로 보냄
        pos = 11;
        delay(1000); 
    }
}