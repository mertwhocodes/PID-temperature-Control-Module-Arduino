 # Heater-PID-Control-Module-
![PID_CONTROL_MODULE2](https://user-images.githubusercontent.com/41569309/66596865-626e3900-eba6-11e9-94e7-ca655ca1fff0.jpeg)
**Close loop PID Heater Control Module**

This module designed to control AC Clamp heater or any AC heater with PID algorithm.
That module use Max6675 Cold-Junction-Compensated K-Thermocoupleto-Digital Converter to mesure 
temperature of heater.First you have to include max6675.h on arduino ide.
# **Companent list**
- Max6675
- BTA-16 triac
- Moc3020
- Pc817
- D1208 rectifier
- K-type thermocouple
- 2x47k res
- 100 res
- 200 res
- 1k res
- 0.1µF con
# Installation 
> go get [github.com/merttuncell/Heater-PID-Control-Module-](https://github.com/merttuncell/Heater-PID-Control-Module- )

> add Max6675.h  arduino library from [ https://github.com/adafruit/MAX6675-library]( https://github.com/adafruit/MAX6675-library)
# Arduino Connection
![arduino connection](https://user-images.githubusercontent.com/41569309/66707303-19091f80-ed47-11e9-9d78-c25a557767a2.png)

# Pin Configuration

- **GND** - Ground
- **Frig** - Triger pin for Triac  
- **Z0** - AC Voltage ZeroOut dedection output pin high when [zero cross](https://en.wikipedia.org/wiki/Zero_crossing_control )  dedection
- **SO** - Serial Data Output For MAX6675
- **CS** - Ship Select Set CS low to enable the serial interface 
- **SCK** - Serial Clock Input 
- **VCC** - Positive Supply (3V-5.5V)



# Repository Contents

- **/Documentation** - Datasheets, additional product information

- **/Frimware** - Example code for Arduino

- **/Hardware** - Eagle design files(.brd, .sch)
