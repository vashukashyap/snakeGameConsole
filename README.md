# Snake Game Console
Hi, this is my project "Snake Game Console"
## Configurations
IDE : `PlatformIO`  
Microcontroller  : `ESP8266`  
Peripheral : `oled 0.96 Inch` , `Push Button` , `3.3v lithium-ion Battery` , `TDA2822 IC` , `100uF-50V Polar Capacitor` , `Speaker`  
Library : `Adafruit GFX Library` , `Adafruit SSD1306`

## PINS CONNECTIONS
  D7-->Sound_Output  
  D6-->Left_Button  
  D5-->Right_Button  
  G-->Display_GND / TDA2822_GND  
  3V-->Display_VCC / TDA2822_VCC  
  D4-->Display_SCK  
  D3-->Display_SDA  
  D2-->Down_Button  
  D1-->Up_Button  

## Project SETUP
  You can view hardware folder file in KICAD and firmware flder file in VSCODE just make sure you had installed the PlatformIO extension in the VSCode.
  On opening Firmware folder in vscode platformIO automatically detect its project and do the setup automatically.
  #### Build
  Click on the Build Button which look like this `✓`
  ### Flash
  Click on the Flash Button which look like this `→`


