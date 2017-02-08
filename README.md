Fermentation Chamber Controller
arduino based fermentation chamber temperature controller
    stage one including:
    - Arduino Uno clone
    - lcd display
    - rotary encoder for changing temperature
    - two temperature probes DS18B20 using one wire bus
    - relay for turning compressor on and off
    - relay for turning heater on and off
    
    stage two including:
    - logging using ESP-01 and Ai Thinker commands over hardware serial
    
    stage three including:
    - full control and status via ESP-01
    
   The LCD circuit for the LCD HelloWorld. We will use the same pin configuration:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)
