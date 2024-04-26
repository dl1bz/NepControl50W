//----------------------------------------------------------------------------------------------
//    stuff for using the onboard LED of the ESP32-S3 Zero
//----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// define things for onboard LED at GPIO PIN 21 (fix)
#define RGB_BRIGHTNESS 10      // change LED brightness (max 255)
const int ledPIN = 21;         // onboard LED at GPIO 21 (fix)
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void setLED(const char *color) {
      if (color == "b") {
        neopixelWrite(ledPIN,0,0,RGB_BRIGHTNESS); // LED blue, order GRB, not RGB !!!
      } else if (color == "r") {
        neopixelWrite(ledPIN,0,RGB_BRIGHTNESS,0); // LED red, order GRB, not RGB !!!
      } else if (color == "g") {
        neopixelWrite(ledPIN,RGB_BRIGHTNESS,0,0); // LED green, order GRB, not RGB !!!
      } else {
        neopixelWrite(ledPIN,0,0,0);              // LED off, order GRB, not RGB !!!
      }
  delay(50);                                      // delay after switch LED
}
//-----------------------------------------------------------------------------------------
