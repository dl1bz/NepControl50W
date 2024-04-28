# NepControl for the RF Amplifier Neptune 50W with automatic band switch

add an ESP32 to control the amp better and fix the issue (PA switched OFF because faulty frequency detection) in mode SSB.

The issue isn't a really issue (PA switched back to OFF/bypass) - is a decision of the manufacturers device firmware design to protect the LPF against wrong band selection.
For me this design in it's form is not acceptable, because it breaks the normal use of this PA in mode SSB and in my case if running FT8 too.

Solution: I take the control over the main control signals like BIAS on/off and RX/TX relais with my own ESP32 controller and changed PA switch logic, which fix this "issue" completly. It's gone after my mod.
