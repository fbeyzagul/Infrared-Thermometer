/*
    Firmware P/N: 24-02-TRM-500, Rev1
    This sample program is written for a contact thermometer which have the following 
    basic components:
    - Arduino Pro Mini (ATMEGA328) with USB to UART convertor for programming,
    - 1.3" 240X240 pixel TFT screen with SPI communication,
    - MCP3421 ADC with I2C comminication,
    - LM60BIM3 or MCP9700 analog temperature sensor connected to A0 input of Pro Mini
    Code P/N: 09-TMP-401_Rev1
 */


#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MLX90614.h"

Adafruit_MLX90614 mcp;
 
// Pin definitions
#define TFT_CS    7
#define TFT_RST    11
#define TFT_DC     10
#define SCR_WD   240
#define SCR_HT   240   // 320 - to allow access to full 240x320 frame buffer
#define MONITOR_PIN 6
#define  LM35_pin  A0

// Create an instance of the Adafruit ST7735 library
Adafruit_ST7789 lcd = Adafruit_ST7789(TFT_DC, TFT_RST, TFT_CS);

float adcVal;
float temp_Amb;
float Rsense;
float Tsense;
int samples_to_average = 100;
 
void setup() {

  Serial.begin(115200);

/*  while (!Serial) {
    delay(10); // Wait for serial port to connect. Needed for native USB port only
  }

  // Begin can take an optional address and Wire interface
  if (!mcp.begin(0x68, &Wire)) { 
    Serial.println("Failed to find MCP3421 chip");
    while (1) {
      delay(10); // Avoid a busy-wait loop
    }
  }

  Serial.println("MCP3421 Found!");

  // Options: GAIN_1X, GAIN_2X, GAIN_4X, GAIN_8X
  mcp.setGain(GAIN_1X);
  Serial.print("Gain set to: ");
  switch (mcp.getGain()) {
    case GAIN_1X: Serial.println("1X"); break;
    case GAIN_2X: Serial.println("2X"); break;
    case GAIN_4X: Serial.println("4X"); break;
    case GAIN_8X: Serial.println("8X"); break;
  }

  // The resolution affects the sample rate (samples per second, SPS)
  // Other options: RESOLUTION_14_BIT (60 SPS), RESOLUTION_16_BIT (15 SPS), RESOLUTION_18_BIT (3.75 SPS)
  mcp.setResolution(RESOLUTION_16_BIT); // 15 SPS (16-bit)
  Serial.print("Resolution set to: ");
  switch (mcp.getResolution()) {
    case RESOLUTION_12_BIT: Serial.println("12 bits"); break;
    case RESOLUTION_14_BIT: Serial.println("14 bits"); break;
    case RESOLUTION_16_BIT: Serial.println("16 bits"); break;
    case RESOLUTION_18_BIT: Serial.println("18 bits"); break;
  }

  // Test setting and getting Mode
  mcp.setMode(MODE_CONTINUOUS); // Options: MODE_CONTINUOUS, MODE_ONE_SHOT
  Serial.print("Mode set to: ");
  switch (mcp.getMode()) {
    case MODE_CONTINUOUS: Serial.println("Continuous"); break;
    case MODE_ONE_SHOT: Serial.println("One-shot"); break;
  }
*/
  lcd.init(SCR_WD, SCR_HT);
  lcd.fillScreen(BLACK);
  lcd.setCursor(0, 0);
  lcd.setTextColor(WHITE,BLUE);
  lcd.setTextSize(2);
//  lcd.println("HELLO WORLD");

  analogReference(INTERNAL);    // set positive reference voltage to 1.1V
  pinMode(MONITOR_PIN, OUTPUT);  
 
  // Display a welcome message
  lcd.setCursor(20, 40);
  lcd.println("24-02-TRM-500_Rev1");
  delay(2500);
 
}
 
void loop() {

/*    if (mcp.isReady()) {
        int32_t adcValue = mcp.readADC(); // Read ADC value
        float Vsense = 0.0625*adcValue;
        Rsense = 0.000001*Vsense*Vsense + 0.0115*Vsense + 99.061;
        Tsense = (Rsense - 100)/0.389;
        
        Serial.print("  Sens_readimg: ");
        Serial.print(adcValue); 
        Serial.print("  Vsense: ");
        Serial.print(Vsense);            
        Serial.print("  Rsense: ");
        Serial.print(Rsense,2); 
        Serial.print("  Tsense: ");
        Serial.print(Tsense,2); 
    
    
    }
    uint32_t  adcVal_sum = 0;
    digitalWrite(MONITOR_PIN, HIGH);

    int mV = analogRead(LM35_pin); 
    Serial.print(" Ambient_mV :  ");
    Serial.print(mV);
    
    for (int i=0; i < samples_to_average; i++){			// ADC Channel-0 /A0) "samples_to_average" sayısı kadar ölçülür ve toplamı alınır
      int  adcVal_i = analogRead(LM35_pin);                         
      adcVal_sum = adcVal_sum + adcVal_i;
    }

    Serial.print("   Sum:  ");
    Serial.println(adcVal_sum);
    digitalWrite(MONITOR_PIN, LOW);
    adcVal = 1.0742*((adcVal_sum / samples_to_average)- 465);			// Toplam, örnekleme sayısına (samples_to_average) bölünerek ortalama alınır
    temp_Amb = adcVal/10;

*/
      lcd.fillScreen(BLACK);
      lcd.setCursor(20, 40);
      lcd.setTextColor(YELLOW);  // set text color to red and yellow background
      lcd.setTextSize(3);
    //  lcd.print(Tsense, 1);
      lcd.print("Body=35.0");
    //  lcd.drawCircle(103, 25, 3, YELLOW);       // print degree symbol ( ° )
      lcd.print(" C");
      
      lcd.setCursor(20, 140);
      lcd.setTextColor(YELLOW);  // set text color to red and yellow background
      lcd.setTextSize(3);
    //  lcd.print("Ambient:");  
      lcd.print("Amb=23.1");    
    //  lcd.print(temp_Amb, 1);
    //  lcd.drawCircle(95, 60, 1, YELLOW);       // print degree symbol ( ° )
      lcd.print(" C");
      delay(1000);   
}
