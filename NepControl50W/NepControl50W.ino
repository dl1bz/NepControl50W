/*
  alternate Control of the Neptune 50W by 60dbm.com with automatic band switching
  using an WAVESHARE ESP32-S3 Zero
  idea by DL1BZ & developed by DL1BZ

  CONDITIONS you need to agree if want using my modification:
  +---------------------------------------------------------------------------------+
  | No warranty, no guarantee that everything works correctly!                      |
  | All what you do is at your own risk !                                           |
  | For amateur radio use only !                                                    |
  | No software support from me, you can use or change the code for free "as it is" |
  +---------------------------------------------------------------------------------+

  End of April in 2024:
  This modification fixed the issue in mode SSB and digimodes with the Neptune 50W amplifier.
  Background is a faulty and instable frequency detection for switching the LPF in mode SSB and digimodes.
  The manufacturer of this amp has decided in his firmware, that in this case the amp switched back to OFF/bypass.
  We change this situation by changing the control logic of the amp, what means we "overwrite" this protection,
  the amp don't switched OFF now anymore in this case.
  
  The uC STM32 inside the amp continues to handle automatic band switching

  --> Be sure to follow the following steps: <--
      1. FIRST tune ever with LOW input power and a pure carrier RF signal, that the amp detect the correct band !
         Repeat this EVER if you change the band !
      2. THEN you can use the AMP how you want, no more issues with SSB or digimodes like FT8 & Co.
      3. check that the RF output increases not more than 50W, otherwise reduce the input RF power

      Max. input RF power is 5W !

*/

// read global project config
#include "config.h"

// other includes
#include "onboard_LED.h"        // control the onboard LED
#include "amp_control.h"        // switch signals for the amp at the GPIO

//-----------------------------------------------------------------------------------------
// init all UARTs
void init_UARTs() {
  Serial.end();                                 // 1 = means full terminate
  // Serial1.end();
  // Serial2.end(1);
  delay(100);
  // Serial1.setRxBufferSize(SER_BUF_SIZE);          // set new UART buffer size
  Serial.begin(115200);                              // initialize internal UART0 with 115200/8N1
  // Serial1.begin(9600, SERIAL_8N1, RxD1, TxD1);    // initialize external UART1 with 9600/8N1
  // Serial2.begin(9600, SERIAL_8N1, RxD2, TxD2);    // initialize external UART2 with 9600/8N1
  // delay(100);
  #ifdef DEBUG
  Serial.println("Serial0 TXD is on pin: "+String(TX));
  Serial.println("Serial0 RXD is on pin: "+String(RX));
  // Serial.println("Serial1 TXD is on pin: "+String(TxD1));
  // Serial.println("Serial1 RXD is on pin: "+String(RxD1));
  // Serial.println("Serial2 TXD is on pin: "+String(TxD2));
  // Serial.println("Serial2 RXD is on pin: "+String(RxD2));
  #endif
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// init ESP32 PINs for digital in/out, the PINs are defined further up
void init_GPIO() {
  pinMode(pttPIN, INPUT_PULLUP);    // PIN input from the PTT line at RCA Socket, LOW ACTIVE with internal PullUp activated for reliable detection
  // pinMode(ptt2PIN, INPUT_PULLUP);   // PIN input from the Sub-D socket, LOW ACTIVE with internal PullUp activated for reliable detection
  // pinMode(pttPIN, INPUT);        // PIN input from the PTT line, LOW ACTIVE without using internal PullUp
  pinMode(biasPIN, OUTPUT);         // PIN output BIAS
  pinMode(pwrPIN, INPUT_PULLDOWN);  // PIN input Power ON
  pinMode(txPIN, OUTPUT);           // PIN output for RX/TX relais
  pinMode(txLedPIN, OUTPUT);        // PIN output for TX LED
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
setLED("off");          // onboard LED off
setLED("b");            // set onboard LED to blue

init_UARTs();           // init UARTs
init_GPIO();            // init GPIOs

Serial.println(VERSION);              // print Version
Serial.print("This application is using ESP-SDK: "); Serial.println(ESP.getSdkVersion());

delay(1000);            // wait 1s

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:
  bool PTTState;
  bool ON_LEDState;

  PTTState = !digitalRead(pttPIN);    // read PTT input line at GPIO input PIN and negotiate it, because PTT line of PA is Low active: RX=H TX=L
  ON_LEDState = digitalRead(pwrPIN);  // read ON LED input state

  //--- MAIN CONTROL ROUTINE OF AMP ---|
  // amp will be switched on only if PTT = ON and ON_LED is ON (means Amp is powered ON with the ON button)
    if (PTTState && ON_LEDState) {
      ampSW(1);  // amp on
    } else {
      ampSW(0);  // amp off
    }
  //-----------------------------------|

  // here we using an exact timer with millis(), time is defined with timerDelay
  if ((millis() - lastTime) > timerDelay) {
  
  // debug output if needed
    #ifdef DEBUG
    Serial.print(" ON LED: ");Serial.print(digitalRead(pwrPIN));
    Serial.print(" PTT_RCA: ");Serial.print(PTTState);
    // Serial.print("PTT_2: ");Serial.print(PTT2State);
    Serial.print(" BIAS: ");Serial.print(digitalRead(biasPIN));
    Serial.print(" TX Relais: ");Serial.print(digitalRead(txPIN));
    Serial.print(" TX LED: ");Serial.println(digitalRead(txLedPIN));
    #endif

    // gimmick: blinking LEDs as heartbeat visualisation to show the running program is alive
    if (G_LEDState) {
      setLED("g");             // onboard LED green
      // pwr_LED(G_LEDState);  
    } else {
      setLED("r");             // onboard LED red
      // pwr_LED(G_LEDState);
    }
    G_LEDState = !G_LEDState;  // negotiate LED state for the next loop run, we want a blinking LED :-)

  lastTime = millis();
  }
}
//-----------------------------------------------------------------------------------------