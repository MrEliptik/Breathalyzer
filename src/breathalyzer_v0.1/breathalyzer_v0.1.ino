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

#define MQ3_MINSENTIVITY_VOLTAGE 2.5

#define ORDER2CONVERSION(x) 189.6643023*x*x-1031.588101*x+1424.9366
#define ORDER3CONVERSION(x) 230.1310332*x*x*x-2053.119259*x*x+6056.723285*x-5794.647575
#define ORDER4CONVERSION(x) 192.0543743*x*x*x*x-2314.144242*x*x*x+10374.40878*x*x-20406.38971*x+14876.27983

void setup() {

  /* to Delete */
  Serial.begin(9600);
  
  pinMode(USR_BTN1, INPUT);
  pinMode(A_MQ3, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  //display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
    
}

void loop() {

  float MQ3Voltage;
  double alcohol;

  MQ3Voltage = getMQ3Voltage( 100);

  Serial.print("\r\nMQ3Voltage:");
  Serial.print(MQ3Voltage);
  
  if( getAlcohol( MQ3Voltage, &alcohol, 4)) {
    Serial.print("    Alcohol:");
    Serial.print(alcohol);
    Serial.print("mg/L");  
  }
  
  delay(1000);
     
  /* // Show image buffer on the display hardware.
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
  display.display();*/
}

/*
 * @fn    float getMQ3Voltage( int numberOfMeasures)
 * @brief Get the Average of measurements series
 * 
 * @param numberOfMeasures The length of measurements series
 * @return Voltage read
 */
float getMQ3Voltage( int numberOfMeasures) {
 
  uint16_t adc_MQ;

  /* loop for measurement */
  for( int i=0; i<numberOfMeasures; i++) {
    adc_MQ += analogRead(A7); 
  }

  /* Average of the measures */
  adc_MQ = adc_MQ/numberOfMeasures;

  /* conversion */
  return adc_MQ*(5.0/1023.0);
}

/*
 * @fn      boolean getAlcohol( float voltage, double *alcohol, int order)
 * @brief   Get the Alcohol level after conversion
 * 
 * @details The fuction returns false if the conversion can't be calculate.
 * 
 * @warning Conversion order must be in between 2 and 4
 * 
 * @param   voltage Analog voltage measure
 * @param   alcohol Alchol level
 * @param   order   Conversion order
 * @return  Conversion state
 *          <br/>true : conversion done
 *          <br/>false : conversion did not calculated
 */
boolean getAlcohol( float voltage, double *alcohol, int order) {

  if( voltage<MQ3_MINSENTIVITY_VOLTAGE) {
    return false;
  }

  switch( order) {
    case 2:
      *alcohol = ORDER2CONVERSION( voltage);
      return true;
    break;
    case 3:    
      *alcohol = ORDER3CONVERSION( voltage);
      return true;
    break;
    case 4:
      *alcohol = ORDER4CONVERSION( voltage);
      return true;
    break;
    default :
      return false;
    break;
  }
  
}

