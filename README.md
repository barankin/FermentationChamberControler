# Fermentation Chamber Controller
arduino based fermentation chamber temperature controller

* Stage one including:
 * Arduino Nano
 * 1602 LCD display
 * Rotary encoder for changing temperature
 * Two temperature probes DS18B20 using one wire bus
 * Relay for turning compressor on and off
 * Relay for turning heater on and off
* Stage two including:
 * Logging using ESP-01 and Ai Thinker commands over hardware serial
* Stage three including:
 * Full control and status via ESP-01

# Background
* The LCD circuit for the LCD HelloWorld. We will use the same pin configuration:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
