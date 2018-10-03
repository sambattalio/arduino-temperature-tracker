# arduino-temperature-tracker
This project was created with a partner in the Embedded Systems course at Notre Dame.
It is an Arduino thermostat display, which reads and displays the current temperature on an LCD. 
In addition, it allows a user to define a set temperature using a potentiometer to which the temperature reading is compared.
It then identifies the current temperature reading as colder or warmer than the set temperature with the brightness of a blue or red LED, respectively.
Furthermore, the Arduino has a button linked via interrupt which switches the displayed temperatures between Fahrenheit and Celsius.

# Wiring

![Wiring Diagram](https://raw.githubusercontent.com/sambattalio/arduino-temperature-tracker/master/Screen%20Shot%202018-10-03%20at%205.36.08%20PM.png)
Created by Sam Battalio and Chris Susco

# Resources used

TMP36 (Temperature Sensor) Datasheet: http://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf
