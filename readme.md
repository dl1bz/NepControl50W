# NepControl for the RF Amplifier Neptune 50W with automatic band switch

add an ESP32 to control the amp better and fix the issue "PA switched OFF because faulty frequency detection" in mode SSB.

The issue isn't a really issue (PA switched back to OFF/bypass) - is a decision of the manufacturers device firmware design to protect the LPF against wrong band selection.
For me this design in it's form is not acceptable, because it breaks the normal use of this PA in mode SSB and in my case if running FT8 too.

Solution: I take the control over the main control signals like BIAS on/off and RX/TX relais with my own ESP32 controller and changed PA switch logic, which fix this "issue" completly. The "issue" is gone after my mod.

*But be careful:* FIRST set a pure carrier tune signal with low power, that the PA can detect the band reliable (this works in this case) - that ALWAYS has to be the FIRST STEP if changing the band ! AFTER this you can transmit in SSB or other modes.

My mod is only allowed under this condition, because my mod remove the protection, which is causing the issue with SSB. A wrong band selection can damage the LPF capacitors !

If you want to use my mod, you confirm the following:<BR>
No guarantee, no warranty !<BR>
You do all at your own risk !<BR>
You know, what you do !<BR>
Only for use in amateur radio, because you need to be a licensed hamradio operator !
