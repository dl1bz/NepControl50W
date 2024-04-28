# NepControl for the RF Amplifier Neptune 50W with automatic band switch

add an ESP32 to control the amp better and fix the issue (PA switched OFF because faulty frequency detection) in mode SSB.
The issue isn't a really issue (PA switched back to OFF/bypass) - is a decision of the manufacturers device firmware design to protect the LPF against wrong band selection.
For me this design in it's form is not acceptable, because it breaks the normal use of this PA.

Solution: I "overwrite" the main control signals like BIAS on/off and RX/TX relais with my own ESP32 controller, which fix this "issue" completly.
