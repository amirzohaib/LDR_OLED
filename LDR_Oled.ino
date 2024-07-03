/***************************************************************************
This Program Takes in Analog values from LDR and converts them to a value 0-100% and displays it on OLED 
 ***************************************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>



/***************************************************************************
OLED 
 ***************************************************************************/

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

/***************************************************************************
LDR
 ***************************************************************************/
#define ldr  33 

unsigned char sun_icon[] ={
  0b00000000, 0b00000000, //        Icon for Sun         
  0b00100000, 0b10000010, //   #     #     # 
  0b00010000, 0b10000100, //    #    #    #  
  0b00001000, 0b00001000, //     #       #   
  0b00000001, 0b11000000, //        ###      
  0b00000111, 0b11110000, //      #######    
  0b00000111, 0b11110000, //      #######    
  0b00001111, 0b11111000, //     #########   
  0b01101111, 0b11111011, //  ## ######### ##
  0b00001111, 0b11111000, //     #########   
  0b00000111, 0b11110000, //      #######    
  0b00000111, 0b11110000, //      #######    
  0b00010001, 0b11000100, //    #   ###   #  
  0b00100000, 0b00000010, //   #           # 
  0b01000000, 0b10000001, //  #      #      #
  0b00000000, 0b10000000, //         #       
};


void setup() {

/***************************************************************************
Serial Setup 
 ***************************************************************************/
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb

 /***************************************************************************
OLED Setup 
 ***************************************************************************/
 // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextColor(WHITE);
  delay(1000); // Pause for 1 Sec
}

void loop() {

  /***************************************************************************
 Draw Images and Sensor Data on Display
 ***************************************************************************/

  display.clearDisplay();
  display.setTextSize(2);
  display.drawBitmap(33, 7, sun_icon, 16, 16 ,1);
  display.setCursor(53, 7);
  int ldrReading = map(analogRead(ldr), 0, 4095, 100, 0);
  display.print(ldrReading);
  display.print(" %");
  display.setCursor(7, 30);
  display.print("Luminosity");

  display.display(); 


  /***************************************************************************
 Serial Monitor Data Output
 ***************************************************************************/

    Serial.print("LDR Reading:");
    Serial.print(ldrReading);
    Serial.print("\n");
  //Serial.println();
    
    //delay(2000);  //Update all values every 2 Seconds

}
