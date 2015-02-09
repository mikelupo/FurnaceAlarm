#FurnaceAlarm

Contained here is the code for a FurnaceAlarm device type that will work with anan Arduino board and a Smartthings Shield for Adruino. The adruino detects a relay closure on PIN 2 and then sends a message to the Smartthings cloud (smartthing.send("some string"). From there, the groovy code takes over and should be able to send a push message to your ST client on your mobile phone. 
My furnace electrical box is a Honeywell R7184U.

Requirements:
your furnace's electronics must have an alarm or trouble feature. 
An Arduino board
A Smartthings shield for Arduino. 



