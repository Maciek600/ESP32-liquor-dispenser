# ESP32 Alcohol Dispenser with Scale
## The goal of the project was to create a beverage dispenser with a built-in scale that precisely controls the amount of liquid poured. The device automatically dispenses the user-specified amount of liquid, measured based on the weight of the cup or glass.

The user places a glass on a base with an integrated scale (load cell). When the distance sensor detects the presence of a glass, the scale resets, and the user selects the desired amount of beverage using a control panel with buttons. After confirmation, the device automatically starts pouring, continuously monitoring the weight and precisely stopping the dispensing once the selected amount is reached. If no container is detected or the limit is reached, the system displays an appropriate message.

## The schematic and design were created using Autodesk Eagle.
The code was written using Arduino IDE.
