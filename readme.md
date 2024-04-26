# NepControl for the RF Amplifier Neptune 50W with automatic band switch

add an ESP32 to control the amp better and fix the issues with the faulty frequency detection in mode SSB.
We "overwrite" some control signals like BIAS on/off and RX/TX relais, otherwise the amp will be switched off the transmission and fall back to bypass state.
 