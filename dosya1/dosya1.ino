#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST   8
#define TFT_DC     9
#define BUTTON_PIN 6
#define BUZZER_PIN 5

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

bool deviceOn = false;
const int measurementCount = 500;

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
  //  pinMode(BUZZER_PIN, OUTPUT);
    
    Wire.begin();
    mlx.begin();
    tft.init(240, 240);
    tft.setRotation(2);
    tft.fillScreen(ST77XX_WHITE);
}

void loop() {
  digitalWrite(BUZZER_PIN, LOW);
  tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(50, 100);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.print("Temp: ");
    //tft.print(avgTemp);
    tft.println(" C");

    if (digitalRead(BUTTON_PIN) == LOW) {
        delay(200);
        deviceOn = !deviceOn;
        
        if (deviceOn) {
            tft.fillScreen(ST77XX_WHITE);
        } else {
            tft.fillScreen(ST77XX_WHITE);
        }
        while (digitalRead(BUTTON_PIN) == LOW); // Buton bırakılana kadar bekle
    }
    
    if (deviceOn) {
        if (digitalRead(BUTTON_PIN) == LOW) {
            delay(200);
            measureTemperature();
        }
    }
}

void measureTemperature() {
    float totalTemp = 0.0;
    for (int i = 0; i < measurementCount; i++) {
        totalTemp += mlx.readObjectTempC();
        delay(5);
    }
    float avgTemp = totalTemp / measurementCount;
    
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(50, 100);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.print("Temp: ");
    tft.print(avgTemp);
    tft.println(" C");
    
    //digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    //digitalWrite(BUZZER_PIN, LOW);
}
