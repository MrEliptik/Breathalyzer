/**********************************************************************;
* Project           : Breathalyzer
*
* Program name      : Breathalyzer_v0.1
*
* Author            : Victor MEUNIER
*
* Date created      : 20180623
*
* Purpose           : Create a simple and user friendly Arduino based
*                     breathalyzer.
*
* Revision History  : 
*
* Date        Author        Ref     Revision (Date in YYYYMMDD format) 
* 20180623    V.Meunier     v0.1    Creation of v0.1

**********************************************************************/
// I2C communication
#include <SPI.h>
#include <Wire.h>

// Special effects
#include <Adafruit_GFX.h>

// OLED driver
#include <Adafruit_SSD1306.h>

#define USR_BTN1      3
#define LED1          2
#define BUZZER        4
#define D_MQ3         X
#define A_MQ3         A7
#define TEMP_SENS     X

#define SDA           A4
#define SCL           A5


void setup() {
  pinMode(USR_BTN1, INPUT);
  pinMode(A_MQ3, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
    
}

void loop() {
   // Show image buffer on the display hardware.
  display.display();

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, WHITE);

  // draw a white circle, 10 pixel radius
  display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
  display.display();
  
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");

   // miniature bitmap display
  display.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
  display.display();

}
