//-----------------------------------------------------------------------------------------
void ampSW(bool sw) {
  // var sw = true => amp ON, sw = false => amp OFF
  if (sw) {
    digitalWrite(txPIN,1);    // switch RX/TX relais to TX
    delay(G_PTTDelay);        // short delay before bias switch on
    digitalWrite(biasPIN,1);  // set bias switch on for power up the MOSFETs
    digitalWrite(txLedPIN,1); // TX LED on
  } else {
    digitalWrite(biasPIN,0);  // switch MOSFET bias OFF
    digitalWrite(txPIN,0);    // switch RX/TX relais to RX/bypass
    digitalWrite(txLedPIN,0); // TX LED off
  }
}
//-----------------------------------------------------------------------------------------